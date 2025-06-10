#include "SettingsManager.h"

#include <QApplication>
#include <QStandardPaths>
#include <QDir>

const QString SettingsManager::DEFAULT_THEME = "light";

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    , m_settings(nullptr)
{
    QApplication::setOrganizationName("TextEditor");
    QApplication::setOrganizationDomain("texteditor.local");
    QApplication::setApplicationName("Multi-Tab Editor");
    
    m_settings = new QSettings(this);
    initializeDefaults();
}

SettingsManager::~SettingsManager()
{
}

void SettingsManager::initializeDefaults()
{
    if (!m_settings->contains("font")) {
        QFont defaultFont("Consolas", 10);
        defaultFont.setFixedPitch(true);
        saveFont(defaultFont);
    }
    
    if (!m_settings->contains("theme")) {
        saveTheme(DEFAULT_THEME);
    }
    
    if (!m_settings->contains("wordWrap")) {
        saveWordWrap(false);
    }
    
    if (!m_settings->contains("lineNumbers")) {
        saveLineNumbers(true);
    }
    
    if (!m_settings->contains("autoIndent")) {
        saveAutoIndent(true);
    }
    
    if (!m_settings->contains("tabWidth")) {
        saveTabWidth(DEFAULT_TAB_WIDTH);
    }
    
    if (!m_settings->contains("syntaxHighlighting")) {
        saveSyntaxHighlighting(true);
    }
    
    if (!m_settings->contains("lastOpenDirectory")) {
        QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        saveLastOpenDirectory(homeDir);
    }
}

void SettingsManager::saveWindowGeometry(const QByteArray &geometry)
{
    m_settings->setValue("geometry", geometry);
}

QByteArray SettingsManager::loadWindowGeometry() const
{
    return m_settings->value("geometry").toByteArray();
}

void SettingsManager::saveWindowState(const QByteArray &state)
{
    m_settings->setValue("windowState", state);
}

QByteArray SettingsManager::loadWindowState() const
{
    return m_settings->value("windowState").toByteArray();
}

void SettingsManager::saveRecentFiles(const QStringList &files)
{
    m_settings->setValue("recentFiles", files);
}

QStringList SettingsManager::loadRecentFiles() const
{
    return m_settings->value("recentFiles").toStringList();
}

void SettingsManager::addRecentFile(const QString &filePath)
{
    QStringList files = loadRecentFiles();
    files.removeAll(filePath);
    files.prepend(filePath);
    
    while (files.size() > MAX_RECENT_FILES) {
        files.removeLast();
    }
    
    saveRecentFiles(files);
}

void SettingsManager::removeRecentFile(const QString &filePath)
{
    QStringList files = loadRecentFiles();
    files.removeAll(filePath);
    saveRecentFiles(files);
}

void SettingsManager::saveFont(const QFont &font)
{
    m_settings->setValue("font", font);
    emit settingsChanged();
}

QFont SettingsManager::loadFont() const
{
    QFont defaultFont("Consolas", 10);
    defaultFont.setFixedPitch(true);
    return m_settings->value("font", defaultFont).value<QFont>();
}

void SettingsManager::saveTheme(const QString &theme)
{
    m_settings->setValue("theme", theme);
    emit settingsChanged();
}

QString SettingsManager::loadTheme() const
{
    return m_settings->value("theme", DEFAULT_THEME).toString();
}

void SettingsManager::saveWordWrap(bool enabled)
{
    m_settings->setValue("wordWrap", enabled);
    emit settingsChanged();
}

bool SettingsManager::loadWordWrap() const
{
    return m_settings->value("wordWrap", false).toBool();
}

void SettingsManager::saveLineNumbers(bool enabled)
{
    m_settings->setValue("lineNumbers", enabled);
    emit settingsChanged();
}

bool SettingsManager::loadLineNumbers() const
{
    return m_settings->value("lineNumbers", true).toBool();
}

void SettingsManager::saveAutoIndent(bool enabled)
{
    m_settings->setValue("autoIndent", enabled);
    emit settingsChanged();
}

bool SettingsManager::loadAutoIndent() const
{
    return m_settings->value("autoIndent", true).toBool();
}

void SettingsManager::saveTabWidth(int width)
{
    m_settings->setValue("tabWidth", width);
    emit settingsChanged();
}

int SettingsManager::loadTabWidth() const
{
    return m_settings->value("tabWidth", DEFAULT_TAB_WIDTH).toInt();
}

void SettingsManager::saveLastOpenDirectory(const QString &directory)
{
    m_settings->setValue("lastOpenDirectory", directory);
}

QString SettingsManager::loadLastOpenDirectory() const
{
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return m_settings->value("lastOpenDirectory", homeDir).toString();
}

void SettingsManager::saveSessionFiles(const QStringList &files)
{
    m_settings->setValue("sessionFiles", files);
}

QStringList SettingsManager::loadSessionFiles() const
{
    return m_settings->value("sessionFiles").toStringList();
}

void SettingsManager::saveSyntaxHighlighting(bool enabled)
{
    m_settings->setValue("syntaxHighlighting", enabled);
    emit settingsChanged();
}

bool SettingsManager::loadSyntaxHighlighting() const
{
    return m_settings->value("syntaxHighlighting", true).toBool();
}

