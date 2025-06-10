/**
 * @file MainWindow.h
 * @brief Main application window class for the Multi-Tab Text Editor
 * @author Multi-Tab Editor Team
 * @date 2025
 */

#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QDockWidget>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QTimer>
#include <memory>

#include "SettingsManager.h"

class TabWidget;
class TextEditor;
class FileExplorer;
class FindReplacePanel;
class ThemeManager;

/**
 * @class MainWindow
 * @brief The main application window managing the text editor interface
 * 
 * MainWindow serves as the primary interface for the Multi-Tab Text Editor application.
 * It coordinates all major components including:
 * - Tab management for multiple documents
 * - Menu and toolbar actions
 * - File operations (open, save, recent files)
 * - Search and replace functionality
 * - Session management and auto-save
 * - Error handling and user notifications
 * 
 * The class follows Qt's Model-View architecture and implements comprehensive
 * error handling, session persistence, and modern text editing features.
 * 
 * @see TabWidget, TextEditor, FileExplorer
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the main window
     * @param parent Parent widget (typically nullptr for main window)
     * 
     * Initializes all UI components, sets up signal connections,
     * loads user settings, and starts auto-save timers.
     */
    explicit MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor - saves settings and performs cleanup
     */
    ~MainWindow();

protected:
    /**
     * @brief Handles application close event
     * @param event Close event to process
     * 
     * Prompts user to save unsaved changes, saves session data,
     * and performs cleanup before closing.
     */
    void closeEvent(QCloseEvent *event) override;

private slots:
    /** @brief Creates a new empty document in a new tab */
    void newFile();
    
    /** @brief Opens a file dialog to select and open a file */
    void openFile();
    
    /**
     * @brief Opens a specific file by path
     * @param filePath Path to the file to open
     * 
     * Performs file validation, large file warnings, and error handling
     * before opening the file in a new tab.
     */
    void openFile(const QString &filePath);
    
    /** @brief Saves the current document */
    void saveFile();
    
    /** @brief Opens save dialog to save current document with new name */
    void saveFileAs();
    
    /** @brief Saves all modified documents */
    void saveAllFiles();
    
    /** @brief Closes the current tab */
    void closeTab();
    
    /** @brief Closes all open tabs */
    void closeAllTabs();
    
    /** @brief Exits the application */
    void exitApplication();
    
    /** @brief Undoes the last text operation */
    void undo();
    
    /** @brief Redoes the last undone operation */
    void redo();
    
    /** @brief Cuts selected text to clipboard */
    void cut();
    
    /** @brief Copies selected text to clipboard */
    void copy();
    
    /** @brief Pastes text from clipboard */
    void paste();
    
    /** @brief Selects all text in current editor */
    void selectAll();
    
    /** @brief Opens the find panel */
    void find();
    
    /** @brief Opens the find and replace panel */
    void replace();
    
    /** @brief Increases font size in current editor */
    void zoomIn();
    
    /** @brief Decreases font size in current editor */
    void zoomOut();
    
    /** @brief Resets font size to default in current editor */
    void resetZoom();
    
    /** @brief Toggles word wrap mode in current editor */
    void toggleWordWrap();
    
    /** @brief Toggles line number visibility in current editor */
    void toggleLineNumbers();
    
    /** @brief Toggles session restore functionality on/off */
    void toggleSessionRestore();
    
    /** @brief Switches to light theme */
    void setLightTheme();
    
    /** @brief Switches to dark theme */
    void setDarkTheme();
    
    /** @brief Switches to automatic theme */
    void setAutoTheme();
    
    /** @brief Opens the preferences dialog (placeholder) */
    void showPreferences();
    
    /** @brief Shows application about dialog */
    void showAbout();
    
    /** @brief Opens a file from the recent files menu */
    void openRecentFile();
    
    /** @brief Clears all recent files from the menu */
    void clearRecentFiles();
    
    /**
     * @brief Handles tab change events
     * @param index Index of the newly selected tab
     */
    void onTabChanged(int index);
    
    /**
     * @brief Handles tab close requests
     * @param index Index of the tab to close
     */
    void onTabCloseRequested(int index);
    
    /** @brief Handles document modification events */
    void onDocumentModified();
    
    /**
     * @brief Handles external file change notifications
     * @param filePath Path of the file that changed externally
     */
    void onFileChangedExternally(const QString &filePath);
    
    /**
     * @brief Handles theme change notifications
     * @param themeName Name of the new theme
     */
    void onThemeChanged(const QString &themeName);

private:
    /** @brief Sets up the main UI layout and central widget */
    void setupUI();
    
    /** @brief Creates and configures the menu bar */
    void setupMenuBar();
    
    /** @brief Creates and configures the toolbar */
    void setupToolBar();
    
    /** @brief Sets up the status bar */
    void setupStatusBar();
    
    /** @brief Creates and configures dock widgets (file explorer, find panel) */
    void setupDockWidgets();
    
    /** @brief Creates all QAction objects and connects signals */
    void createActions();
    
    /** @brief Updates action states based on current editor context */
    void updateActions();
    
    /** @brief Updates window title with current file information */
    void updateWindowTitle();
    
    /** @brief Updates status bar with cursor position and file info */
    void updateStatusBar();
    
    /** @brief Updates recent files menu with current list */
    void updateRecentFileActions();
    
    // Session Management
    /** @brief Saves current session data to settings */
    void saveSession();
    
    /** @brief Restores previous session from settings */
    void restoreSession();
    
    /**
     * @brief Gets current session data for saving
     * @return SessionData structure containing all tab information
     */
    SessionData getCurrentSession() const;
    
    /** @brief Auto-saves content of all modified tabs */
    void autoSaveAllTabs();
    
    /** @brief Starts the auto-save timer with configured interval */
    void startAutoSaveTimer();
    
    /** @brief Checks system memory usage and warns if low */
    void checkMemoryUsage();
    
    /** @brief Creates crash recovery backup files */
    void createCrashRecoveryBackup();
    
    /** @brief Checks for and offers to restore from crash recovery */
    void checkForCrashRecovery();
    
    /**
     * @brief Prompts user to save unsaved changes
     * @return true if safe to continue (saved or discarded), false if cancelled
     */
    bool maybeSave();
    
    /**
     * @brief Saves document at specified tab index
     * @param index Tab index of document to save
     * @return true if save successful, false otherwise
     */
    bool saveDocument(int index);
    
    /** @brief Loads window geometry and state from settings */
    void loadSettings();
    
    /** @brief Saves window geometry and state to settings */
    void saveSettings();

    // Core UI Components
    /** @brief Central tab widget for managing multiple editors */
    TabWidget *m_tabWidget;
    
    /** @brief File explorer dock widget for browsing files */
    FileExplorer *m_fileExplorer;
    
    /** @brief Find and replace panel for text search operations */
    FindReplacePanel *m_findReplacePanel;
    
    /** @brief Settings manager for persistent configuration */
    SettingsManager *m_settingsManager;
    
    /** @brief Theme manager for UI themes and switching */
    ThemeManager *m_themeManager;
    
    // Dock Widgets
    /** @brief Dock widget container for file explorer */
    QDockWidget *m_fileExplorerDock;
    
    /** @brief Dock widget container for find/replace panel */
    QDockWidget *m_findReplaceDock;
    
    // File Menu Actions
    /** @brief Action for creating new files */
    QAction *m_newAction;
    
    /** @brief Action for opening existing files */
    QAction *m_openAction;
    
    /** @brief Action for saving current file */
    QAction *m_saveAction;
    
    /** @brief Action for saving current file with new name */
    QAction *m_saveAsAction;
    
    /** @brief Action for saving all modified files */
    QAction *m_saveAllAction;
    
    /** @brief Action for closing current tab */
    QAction *m_closeTabAction;
    
    /** @brief Action for closing all tabs */
    QAction *m_closeAllTabsAction;
    
    /** @brief Action for exiting application */
    QAction *m_exitAction;
    
    // Edit Menu Actions
    /** @brief Action for undo operation */
    QAction *m_undoAction;
    
    /** @brief Action for redo operation */
    QAction *m_redoAction;
    
    /** @brief Action for cut operation */
    QAction *m_cutAction;
    
    /** @brief Action for copy operation */
    QAction *m_copyAction;
    
    /** @brief Action for paste operation */
    QAction *m_pasteAction;
    
    /** @brief Action for select all operation */
    QAction *m_selectAllAction;
    
    /** @brief Action for find operation */
    QAction *m_findAction;
    
    /** @brief Action for find and replace operation */
    QAction *m_replaceAction;
    
    // View Menu Actions
    /** @brief Action for zooming in */
    QAction *m_zoomInAction;
    
    /** @brief Action for zooming out */
    QAction *m_zoomOutAction;
    
    /** @brief Action for resetting zoom to default */
    QAction *m_resetZoomAction;
    
    /** @brief Action for toggling word wrap */
    QAction *m_wordWrapAction;
    
    /** @brief Action for toggling line numbers */
    QAction *m_lineNumbersAction;
    
    /** @brief Action for toggling session restore functionality */
    QAction *m_sessionRestoreAction;
    
    // Theme Menu Actions
    /** @brief Action for switching to light theme */
    QAction *m_lightThemeAction;
    
    /** @brief Action for switching to dark theme */
    QAction *m_darkThemeAction;
    
    /** @brief Action for switching to automatic theme */
    QAction *m_autoThemeAction;
    
    /** @brief Menu for theme selection */
    QMenu *m_themeMenu;
    
    // Help Menu Actions
    /** @brief Action for opening preferences dialog */
    QAction *m_preferencesAction;
    
    /** @brief Action for showing about dialog */
    QAction *m_aboutAction;
    
    // Recent Files
    /** @brief Menu for recent files */
    QMenu *m_recentFilesMenu;
    
    /** @brief Action for clearing recent files list */
    QAction *m_clearRecentFilesAction;
    
    /** @brief List of recent file actions (up to MAX_RECENT_FILES) */
    QList<QAction*> m_recentFileActions;
    
    // Timers
    /** @brief Timer for auto-save functionality */
    QTimer *m_autoSaveTimer;
    
    /** @brief Timer for memory usage monitoring */
    QTimer *m_memoryCheckTimer;
    
    // Constants
    /** @brief Maximum number of recent files to remember */
    static const int MAX_RECENT_FILES = 10;
    
    /** @brief Auto-save interval in milliseconds (30 seconds) */
    static const int AUTO_SAVE_INTERVAL = 30000;
};