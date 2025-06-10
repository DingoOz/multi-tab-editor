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

// Session Management
void SettingsManager::saveSession(const SessionData &sessionData)
{
    m_settings->beginGroup("Session");
    
    m_settings->setValue("currentTabIndex", sessionData.currentTabIndex);
    m_settings->setValue("restoreSession", sessionData.restoreSession);
    
    m_settings->beginWriteArray("tabs");
    for (int i = 0; i < sessionData.tabs.size(); ++i) {
        m_settings->setArrayIndex(i);
        const SessionTab &tab = sessionData.tabs.at(i);
        
        m_settings->setValue("filePath", tab.filePath);
        m_settings->setValue("content", tab.content);
        m_settings->setValue("isModified", tab.isModified);
        m_settings->setValue("cursorPosition", tab.cursorPosition);
        m_settings->setValue("isUntitled", tab.isUntitled);
        m_settings->setValue("untitledName", tab.untitledName);
    }
    m_settings->endArray();
    
    m_settings->endGroup();
}

SessionData SettingsManager::loadSession() const
{
    SessionData sessionData;
    
    m_settings->beginGroup("Session");
    
    sessionData.currentTabIndex = m_settings->value("currentTabIndex", 0).toInt();
    sessionData.restoreSession = m_settings->value("restoreSession", true).toBool();
    
    int size = m_settings->beginReadArray("tabs");
    sessionData.tabs.reserve(size);
    
    for (int i = 0; i < size; ++i) {
        m_settings->setArrayIndex(i);
        SessionTab tab;
        
        tab.filePath = m_settings->value("filePath").toString();
        tab.content = m_settings->value("content").toString();
        tab.isModified = m_settings->value("isModified", false).toBool();
        tab.cursorPosition = m_settings->value("cursorPosition", 0).toInt();
        tab.isUntitled = m_settings->value("isUntitled", false).toBool();
        tab.untitledName = m_settings->value("untitledName").toString();
        
        sessionData.tabs.append(tab);
    }
    m_settings->endArray();
    
    m_settings->endGroup();
    
    return sessionData;
}

void SettingsManager::clearSession()
{
    m_settings->remove("Session");
}

void SettingsManager::saveRestoreSession(bool enabled)
{
    m_settings->setValue("restoreSession", enabled);
    emit settingsChanged();
}

bool SettingsManager::loadRestoreSession() const
{
    return m_settings->value("restoreSession", true).toBool();
}

// Auto-save for unsaved files
void SettingsManager::saveAutoSaveContent(const QString &tabId, const QString &content)
{
    m_settings->beginGroup("AutoSave");
    m_settings->setValue(tabId, content);
    m_settings->endGroup();
}

QString SettingsManager::loadAutoSaveContent(const QString &tabId) const
{
    m_settings->beginGroup("AutoSave");
    QString content = m_settings->value(tabId).toString();
    m_settings->endGroup();
    return content;
}

void SettingsManager::clearAutoSaveContent(const QString &tabId)
{
    m_settings->beginGroup("AutoSave");
    m_settings->remove(tabId);
    m_settings->endGroup();
}

QStringList SettingsManager::getAutoSaveFiles() const
{
    m_settings->beginGroup("AutoSave");
    QStringList keys = m_settings->childKeys();
    m_settings->endGroup();
    return keys;
}

