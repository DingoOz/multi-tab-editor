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
#include <memory>

class TabWidget;
class TextEditor;
class FileExplorer;
class FindReplacePanel;
class SettingsManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void openFile();
    void openFile(const QString &filePath);
    void saveFile();
    void saveFileAs();
    void saveAllFiles();
    void closeTab();
    void closeAllTabs();
    void exitApplication();
    
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void selectAll();
    void find();
    void replace();
    
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void toggleWordWrap();
    void toggleLineNumbers();
    
    void showPreferences();
    void showAbout();
    
    void onTabChanged(int index);
    void onTabCloseRequested(int index);
    void onDocumentModified();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupDockWidgets();
    void createActions();
    void updateActions();
    void updateWindowTitle();
    void updateStatusBar();
    
    bool maybeSave();
    bool saveDocument(int index);
    void loadSettings();
    void saveSettings();

    TabWidget *m_tabWidget;
    FileExplorer *m_fileExplorer;
    FindReplacePanel *m_findReplacePanel;
    SettingsManager *m_settingsManager;
    
    QDockWidget *m_fileExplorerDock;
    QDockWidget *m_findReplaceDock;
    
    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_saveAllAction;
    QAction *m_closeTabAction;
    QAction *m_closeAllTabsAction;
    QAction *m_exitAction;
    
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_cutAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_selectAllAction;
    QAction *m_findAction;
    QAction *m_replaceAction;
    
    QAction *m_zoomInAction;
    QAction *m_zoomOutAction;
    QAction *m_resetZoomAction;
    QAction *m_wordWrapAction;
    QAction *m_lineNumbersAction;
    
    QAction *m_preferencesAction;
    QAction *m_aboutAction;
};