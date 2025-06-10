#include "ThemeManager.h"
#include "SettingsManager.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>
#include <QPalette>

// Static constants
const QString ThemeManager::LIGHT_THEME = "light";
const QString ThemeManager::DARK_THEME = "dark";
const QString ThemeManager::AUTO_THEME = "auto";
const QString ThemeManager::DEFAULT_THEME = LIGHT_THEME;

ThemeManager::ThemeManager(SettingsManager *settingsManager, QObject *parent)
    : QObject(parent)
    , m_settingsManager(settingsManager)
    , m_currentTheme(DEFAULT_THEME)
    , m_autoThemeEnabled(false)
{
    // Set up themes path - try multiple locations
    QStringList possiblePaths = {
        QDir(QApplication::applicationDirPath()).filePath("../resources/themes"),
        QDir(QApplication::applicationDirPath()).filePath("resources/themes"),
        QDir(QApplication::applicationDirPath()).filePath("../../../resources/themes"), // For build dir
        ":/resources/themes" // From Qt resources
    };
    
    m_themesPath = possiblePaths.first(); // Default fallback
    for (const QString &path : possiblePaths) {
        if (QDir(path).exists() || path.startsWith(":/")) {
            m_themesPath = path;
            break;
        }
    }
    
    // Discover available themes
    discoverThemes();
    
    // Set up system theme monitoring
    setupSystemThemeMonitoring();
}

ThemeManager::~ThemeManager()
{
}

QStringList ThemeManager::getAvailableThemes() const
{
    return m_availableThemes;
}

QString ThemeManager::getCurrentTheme() const
{
    return m_currentTheme;
}

bool ThemeManager::applyTheme(const QString &themeName)
{
    if (themeName == AUTO_THEME) {
        m_autoThemeEnabled = true;
        Theme systemTheme = detectSystemTheme();
        QString actualTheme = themeToString(systemTheme);
        return applyTheme(actualTheme);
    }
    
    m_autoThemeEnabled = false;
    
    if (!isThemeAvailable(themeName)) {
        emit themeError(themeName, tr("Theme not found: %1").arg(themeName));
        return false;
    }
    
    QString stylesheet = loadThemeStylesheet(themeName);
    if (stylesheet.isEmpty()) {
        emit themeError(themeName, tr("Failed to load theme stylesheet: %1").arg(themeName));
        return false;
    }
    
    if (!validateStylesheet(stylesheet)) {
        emit themeError(themeName, tr("Invalid theme stylesheet: %1").arg(themeName));
        return false;
    }
    
    applyStylesheet(stylesheet);
    
    QString previousTheme = m_currentTheme;
    m_currentTheme = themeName;
    
    // Save to settings
    if (m_settingsManager) {
        m_settingsManager->saveTheme(m_autoThemeEnabled ? AUTO_THEME : themeName);
    }
    
    if (previousTheme != m_currentTheme) {
        emit themeChanged(m_currentTheme);
    }
    
    return true;
}

bool ThemeManager::applyTheme(Theme theme)
{
    return applyTheme(themeToString(theme));
}

bool ThemeManager::loadSavedTheme()
{
    QString savedTheme = DEFAULT_THEME;
    if (m_settingsManager) {
        savedTheme = m_settingsManager->loadTheme();
    }
    
    return applyTheme(savedTheme);
}

bool ThemeManager::isThemeAvailable(const QString &themeName) const
{
    if (themeName == AUTO_THEME) {
        return true;
    }
    
    return m_availableThemes.contains(themeName);
}

QString ThemeManager::getThemeDisplayName(const QString &themeName) const
{
    if (themeName == LIGHT_THEME) {
        return tr("Light");
    } else if (themeName == DARK_THEME) {
        return tr("Dark");
    } else if (themeName == AUTO_THEME) {
        return tr("Auto (System)");
    } else {
        // Capitalize first letter for custom themes
        QString displayName = themeName;
        if (!displayName.isEmpty()) {
            displayName[0] = displayName[0].toUpper();
        }
        return displayName;
    }
}

QString ThemeManager::themeToString(Theme theme)
{
    switch (theme) {
        case Theme::Light:
            return LIGHT_THEME;
        case Theme::Dark:
            return DARK_THEME;
        case Theme::Auto:
            return AUTO_THEME;
        case Theme::Custom:
        default:
            return LIGHT_THEME;
    }
}

ThemeManager::Theme ThemeManager::stringToTheme(const QString &themeName)
{
    if (themeName == LIGHT_THEME) {
        return Theme::Light;
    } else if (themeName == DARK_THEME) {
        return Theme::Dark;
    } else if (themeName == AUTO_THEME) {
        return Theme::Auto;
    } else {
        return Theme::Custom;
    }
}

ThemeManager::Theme ThemeManager::detectSystemTheme()
{
    // Check if system supports dark mode detection
    QPalette palette = QApplication::palette();
    QColor windowColor = palette.color(QPalette::Window);
    
    // If window background is dark, assume dark theme
    if (windowColor.lightness() < 128) {
        return Theme::Dark;
    } else {
        return Theme::Light;
    }
}

void ThemeManager::setLightTheme()
{
    applyTheme(Theme::Light);
}

void ThemeManager::setDarkTheme()
{
    applyTheme(Theme::Dark);
}

void ThemeManager::setAutoTheme()
{
    applyTheme(Theme::Auto);
}

void ThemeManager::reloadCurrentTheme()
{
    QString current = m_currentTheme;
    applyTheme(current);
}

void ThemeManager::onSystemThemeChanged()
{
    if (m_autoThemeEnabled) {
        Theme systemTheme = detectSystemTheme();
        QString actualTheme = themeToString(systemTheme);
        if (actualTheme != m_currentTheme) {
            applyTheme(actualTheme);
        }
    }
}

QString ThemeManager::loadThemeStylesheet(const QString &themeName) const
{
    QString filePath = getThemeFilePath(themeName);
    
    // Try to load from Qt resources first
    QString resourcePath = QString(":/resources/themes/%1.qss").arg(themeName);
    QFile resourceFile(resourcePath);
    if (resourceFile.exists() && resourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&resourceFile);
        return in.readAll();
    }
    
    // Fall back to filesystem
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open theme file:" << filePath;
        return QString();
    }
    
    QTextStream in(&file);
    QString stylesheet = in.readAll();
    
    return stylesheet;
}

QString ThemeManager::getThemeFilePath(const QString &themeName) const
{
    return QDir(m_themesPath).filePath(themeName + ".qss");
}

void ThemeManager::applyStylesheet(const QString &stylesheet)
{
    qApp->setStyleSheet(stylesheet);
}

bool ThemeManager::validateStylesheet(const QString &stylesheet) const
{
    // Basic validation - check if stylesheet is not empty and contains some CSS-like content
    if (stylesheet.trimmed().isEmpty()) {
        return false;
    }
    
    // Check for basic QSS patterns
    if (!stylesheet.contains(QRegularExpression(R"(\w+\s*\{)"))) {
        return false;
    }
    
    return true;
}

void ThemeManager::setupSystemThemeMonitoring()
{
    // Note: paletteChanged is deprecated, could use QEvent::ApplicationPaletteChange instead
    // For now, we'll skip system theme monitoring to avoid deprecated API
    // TODO: Implement proper system theme detection using QEvent::ApplicationPaletteChange
}

void ThemeManager::discoverThemes()
{
    m_availableThemes.clear();
    
    // Always add built-in themes from resources
    QStringList builtinThemes = {LIGHT_THEME, DARK_THEME};
    for (const QString &themeName : builtinThemes) {
        QString resourcePath = QString(":/resources/themes/%1.qss").arg(themeName);
        if (QFile::exists(resourcePath)) {
            m_availableThemes << themeName;
        }
    }
    
    // Also check filesystem directory if it exists
    QDir themesDir(m_themesPath);
    if (themesDir.exists() && !m_themesPath.startsWith(":/")) {
        QStringList filters;
        filters << "*.qss";
        
        QFileInfoList themeFiles = themesDir.entryInfoList(filters, QDir::Files);
        
        for (const QFileInfo &fileInfo : themeFiles) {
            QString themeName = fileInfo.baseName();
            if (!m_availableThemes.contains(themeName)) {
                m_availableThemes << themeName;
            }
        }
    }
    
    // Ensure we have at least light and dark themes
    if (!m_availableThemes.contains(LIGHT_THEME)) {
        m_availableThemes << LIGHT_THEME;
    }
    if (!m_availableThemes.contains(DARK_THEME)) {
        m_availableThemes << DARK_THEME;
    }
    
    // Add auto theme option
    m_availableThemes << AUTO_THEME;
    
    // Sort themes (but keep auto at the end)
    QStringList sortedThemes = m_availableThemes;
    sortedThemes.removeAll(AUTO_THEME);
    sortedThemes.sort();
    sortedThemes << AUTO_THEME;
    m_availableThemes = sortedThemes;
}