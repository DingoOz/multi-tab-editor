/**
 * @file SettingsManager.h
 * @brief Settings and session management for persistent application state
 * @author Multi-Tab Editor Team
 * @date 2025
 */

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

/**
 * @struct SessionTab
 * @brief Data structure for storing individual tab information in sessions
 */
struct SessionTab {
    QString filePath;     ///< Full path to the file (empty for untitled)
    QString content;      ///< Content for unsaved/untitled files
    bool isModified;      ///< Whether the tab has unsaved changes
    int cursorPosition;   ///< Cursor position within the document
    bool isUntitled;      ///< Whether this is an untitled document
    QString untitledName; ///< Display name for untitled documents
};

/**
 * @struct SessionData
 * @brief Complete session state for application restoration
 */
struct SessionData {
    QList<SessionTab> tabs; ///< List of all tabs in the session
    int currentTabIndex;    ///< Index of the currently active tab
    bool restoreSession;    ///< Whether session restore is enabled
};

/**
 * @class SettingsManager
 * @brief Manages persistent application settings and session data
 * 
 * SettingsManager provides comprehensive settings persistence using QSettings.
 * It handles:
 * 
 * - Window geometry and state preservation
 * - Recent files list maintenance
 * - Editor preferences (font, theme, behavior)
 * - Session management with complete tab restoration
 * - Auto-save content for crash recovery
 * 
 * The class uses the application's organization and name for settings storage,
 * ensuring settings persist across application runs and system reboots.
 * 
 * @see SessionTab, SessionData, MainWindow
 */
class SettingsManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs settings manager with QSettings initialization
     * @param parent Parent QObject (typically MainWindow)
     */
    explicit SettingsManager(QObject *parent = nullptr);
    
    /**
     * @brief Destructor - ensures settings are properly synced
     */
    ~SettingsManager();

    // Window State Management
    /**
     * @brief Saves main window geometry (size, position)
     * @param geometry Serialized window geometry from saveGeometry()
     */
    void saveWindowGeometry(const QByteArray &geometry);
    
    /**
     * @brief Loads previously saved window geometry
     * @return Serialized geometry data for restoreGeometry()
     */
    QByteArray loadWindowGeometry() const;
    
    /**
     * @brief Saves main window state (dock positions, toolbar state)
     * @param state Serialized window state from saveState()
     */
    void saveWindowState(const QByteArray &state);
    
    /**
     * @brief Loads previously saved window state
     * @return Serialized state data for restoreState()
     */
    QByteArray loadWindowState() const;
    
    // Recent Files Management
    /**
     * @brief Saves complete recent files list
     * @param files List of recent file paths (newest first)
     */
    void saveRecentFiles(const QStringList &files);
    
    /**
     * @brief Loads recent files list
     * @return List of recent file paths (up to MAX_RECENT_FILES)
     */
    QStringList loadRecentFiles() const;
    
    /**
     * @brief Adds file to recent files list (moves to front if exists)
     * @param filePath Full path to the file to add
     */
    void addRecentFile(const QString &filePath);
    
    /**
     * @brief Removes file from recent files list
     * @param filePath Full path to the file to remove
     */
    void removeRecentFile(const QString &filePath);
    
    // Appearance Settings
    /**
     * @brief Saves editor font preferences
     * @param font QFont object with family, size, style
     */
    void saveFont(const QFont &font);
    
    /**
     * @brief Loads editor font preferences
     * @return Previously saved font or system default
     */
    QFont loadFont() const;
    
    /**
     * @brief Saves UI theme preference
     * @param theme Theme identifier (e.g., "light", "dark")
     */
    void saveTheme(const QString &theme);
    
    /**
     * @brief Loads UI theme preference
     * @return Theme identifier or default theme
     */
    QString loadTheme() const;
    
    // Editor Behavior Settings
    /**
     * @brief Saves word wrap preference
     * @param enabled true to enable word wrap by default
     */
    void saveWordWrap(bool enabled);
    
    /**
     * @brief Loads word wrap preference
     * @return true if word wrap should be enabled by default
     */
    bool loadWordWrap() const;
    
    /**
     * @brief Saves line numbers visibility preference
     * @param enabled true to show line numbers by default
     */
    void saveLineNumbers(bool enabled);
    
    /**
     * @brief Loads line numbers visibility preference
     * @return true if line numbers should be visible by default
     */
    bool loadLineNumbers() const;
    
    /**
     * @brief Saves auto-indentation preference
     * @param enabled true to enable auto-indentation
     */
    void saveAutoIndent(bool enabled);
    
    /**
     * @brief Loads auto-indentation preference
     * @return true if auto-indentation is enabled
     */
    bool loadAutoIndent() const;
    
    /**
     * @brief Saves tab width preference
     * @param width Number of spaces per tab (typically 2, 4, or 8)
     */
    void saveTabWidth(int width);
    
    /**
     * @brief Loads tab width preference
     * @return Number of spaces per tab or DEFAULT_TAB_WIDTH
     */
    int loadTabWidth() const;
    
    // File Operation Settings
    /**
     * @brief Saves last directory used for file operations
     * @param directory Path to directory for next file dialog
     */
    void saveLastOpenDirectory(const QString &directory);
    
    /**
     * @brief Loads last directory used for file operations
     * @return Path to last used directory or user's home directory
     */
    QString loadLastOpenDirectory() const;
    
    /**
     * @brief Saves session files list (deprecated - use saveSession instead)
     * @param files List of file paths in session
     */
    void saveSessionFiles(const QStringList &files);
    
    /**
     * @brief Loads session files list (deprecated - use loadSession instead)
     * @return List of file paths from session
     */
    QStringList loadSessionFiles() const;
    
    /**
     * @brief Saves syntax highlighting preference
     * @param enabled true to enable syntax highlighting
     */
    void saveSyntaxHighlighting(bool enabled);
    
    /**
     * @brief Loads syntax highlighting preference
     * @return true if syntax highlighting is enabled
     */
    bool loadSyntaxHighlighting() const;
    
    // Session Management
    /**
     * @brief Saves complete session data including all tabs
     * @param sessionData SessionData structure with tabs and state
     * 
     * Stores all open tabs, their content, modification state, and
     * cursor positions for complete session restoration.
     */
    void saveSession(const SessionData &sessionData);
    
    /**
     * @brief Loads previously saved session data
     * @return SessionData structure with tabs and state, or empty if none
     */
    SessionData loadSession() const;
    
    /**
     * @brief Clears stored session data
     */
    void clearSession();
    
    /**
     * @brief Saves session restore preference
     * @param enabled true to enable automatic session restoration
     */
    void saveRestoreSession(bool enabled);
    
    /**
     * @brief Loads session restore preference
     * @return true if session should be restored on startup
     */
    bool loadRestoreSession() const;
    
    // Auto-save for unsaved files
    /**
     * @brief Saves auto-save content for crash recovery
     * @param tabId Unique identifier for the tab (file path or generated ID)
     * @param content Current text content to save
     */
    void saveAutoSaveContent(const QString &tabId, const QString &content);
    
    /**
     * @brief Loads auto-save content for crash recovery
     * @param tabId Unique identifier for the tab
     * @return Previously saved content or empty string if none
     */
    QString loadAutoSaveContent(const QString &tabId) const;
    
    /**
     * @brief Clears auto-save content for specific tab
     * @param tabId Unique identifier for the tab to clear
     */
    void clearAutoSaveContent(const QString &tabId);
    
    /**
     * @brief Gets list of all auto-save file identifiers
     * @return List of tab IDs that have auto-save content
     */
    QStringList getAutoSaveFiles() const;

signals:
    /**
     * @brief Emitted when any setting is changed
     * 
     * Connected components can use this to update their state
     * when settings are modified.
     */
    void settingsChanged();

private:
    /**
     * @brief Initializes default values for all settings
     * 
     * Called during construction to ensure all settings have
     * reasonable defaults if not previously set.
     */
    void initializeDefaults();
    
    /** @brief Qt settings object for persistent storage */
    QSettings *m_settings;
    
    // Constants
    /** @brief Maximum number of recent files to remember */
    static const int MAX_RECENT_FILES = 10;
    
    /** @brief Default UI theme identifier */
    static const QString DEFAULT_THEME;
    
    /** @brief Default tab width in spaces */
    static const int DEFAULT_TAB_WIDTH = 4;
};