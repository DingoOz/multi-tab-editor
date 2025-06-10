#pragma once

#include <QSettings>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QFont>
#include <QColor>
#include <QSize>
#include <QPoint>
#include <QByteArray>

struct SessionTab {
    QString filePath;
    QString content;    // For unsaved files
    bool isModified;
    int cursorPosition;
    bool isUntitled;
    QString untitledName;
};

struct SessionData {
    QList<SessionTab> tabs;
    int currentTabIndex;
    bool restoreSession;
};

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager();

    void saveWindowGeometry(const QByteArray &geometry);
    QByteArray loadWindowGeometry() const;
    
    void saveWindowState(const QByteArray &state);
    QByteArray loadWindowState() const;
    
    void saveRecentFiles(const QStringList &files);
    QStringList loadRecentFiles() const;
    void addRecentFile(const QString &filePath);
    void removeRecentFile(const QString &filePath);
    
    void saveFont(const QFont &font);
    QFont loadFont() const;
    
    void saveTheme(const QString &theme);
    QString loadTheme() const;
    
    void saveWordWrap(bool enabled);
    bool loadWordWrap() const;
    
    void saveLineNumbers(bool enabled);
    bool loadLineNumbers() const;
    
    void saveAutoIndent(bool enabled);
    bool loadAutoIndent() const;
    
    void saveTabWidth(int width);
    int loadTabWidth() const;
    
    void saveLastOpenDirectory(const QString &directory);
    QString loadLastOpenDirectory() const;
    
    void saveSessionFiles(const QStringList &files);
    QStringList loadSessionFiles() const;
    
    void saveSyntaxHighlighting(bool enabled);
    bool loadSyntaxHighlighting() const;
    
    // Session Management
    void saveSession(const SessionData &sessionData);
    SessionData loadSession() const;
    void clearSession();
    
    void saveRestoreSession(bool enabled);
    bool loadRestoreSession() const;
    
    // Auto-save for unsaved files
    void saveAutoSaveContent(const QString &tabId, const QString &content);
    QString loadAutoSaveContent(const QString &tabId) const;
    void clearAutoSaveContent(const QString &tabId);
    QStringList getAutoSaveFiles() const;

signals:
    void settingsChanged();

private:
    void initializeDefaults();
    
    QSettings *m_settings;
    
    static const int MAX_RECENT_FILES = 10;
    static const QString DEFAULT_THEME;
    static const int DEFAULT_TAB_WIDTH = 4;
};