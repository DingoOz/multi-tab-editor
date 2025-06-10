#include "MainWindow.h"
#include "TabWidget.h"
#include "TextEditor.h"
#include "FileExplorer.h"
#include "FindReplacePanel.h"
#include "SettingsManager.h"

#include <QApplication>
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
#include <QStandardPaths>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tabWidget(nullptr)
    , m_fileExplorer(nullptr)
    , m_findReplacePanel(nullptr)
    , m_settingsManager(nullptr)
    , m_fileExplorerDock(nullptr)
    , m_findReplaceDock(nullptr)
{
    setWindowTitle("Multi-Tab Editor");
    setMinimumSize(800, 600);
    
    m_settingsManager = new SettingsManager(this);
    
    setupUI();
    createActions();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    setupDockWidgets();
    
    loadSettings();
    
    newFile();
}

MainWindow::~MainWindow()
{
    saveSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        saveSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    TextEditor *editor = new TextEditor(this);
    int index = m_tabWidget->addTab(editor, "Untitled");
    m_tabWidget->setCurrentIndex(index);
    editor->setFocus();
    updateActions();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"),
        m_settingsManager->loadLastOpenDirectory(),
        tr("Text Files (*.txt *.cpp *.h *.py *.js *.json *.xml *.html *.css);;All Files (*)"));
    
    if (!fileName.isEmpty()) {
        openFile(fileName);
    }
}

void MainWindow::openFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        QMessageBox::warning(this, tr("Warning"), tr("File does not exist: %1").arg(filePath));
        return;
    }
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot read file %1:\n%2").arg(filePath, file.errorString()));
        return;
    }
    
    QTextStream in(&file);
    QString content = in.readAll();
    
    TextEditor *editor = new TextEditor(this);
    editor->setPlainText(content);
    editor->setFilePath(filePath);
    editor->setModified(false);
    
    int index = m_tabWidget->addTab(editor, fileInfo.fileName());
    m_tabWidget->setCurrentIndex(index);
    
    m_settingsManager->addRecentFile(filePath);
    m_settingsManager->saveLastOpenDirectory(fileInfo.absolutePath());
    
    updateActions();
}

void MainWindow::saveFile()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (!editor) return;
    
    if (editor->filePath().isEmpty()) {
        saveFileAs();
    } else {
        saveDocument(m_tabWidget->currentIndex());
    }
}

void MainWindow::saveFileAs()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (!editor) return;
    
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"),
        m_settingsManager->loadLastOpenDirectory(),
        tr("Text Files (*.txt *.cpp *.h *.py *.js *.json *.xml *.html *.css);;All Files (*)"));
    
    if (!fileName.isEmpty()) {
        editor->setFilePath(fileName);
        saveDocument(m_tabWidget->currentIndex());
    }
}

void MainWindow::saveAllFiles()
{
    for (int i = 0; i < m_tabWidget->count(); ++i) {
        if (m_tabWidget->isTabModified(i)) {
            saveDocument(i);
        }
    }
}

void MainWindow::closeTab()
{
    int index = m_tabWidget->currentIndex();
    if (index >= 0) {
        m_tabWidget->closeTab(index);
    }
}

void MainWindow::closeAllTabs()
{
    m_tabWidget->closeAllTabs();
}

void MainWindow::exitApplication()
{
    close();
}

void MainWindow::undo()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->undo();
    }
}

void MainWindow::redo()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->redo();
    }
}

void MainWindow::cut()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->cut();
    }
}

void MainWindow::copy()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->copy();
    }
}

void MainWindow::paste()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->paste();
    }
}

void MainWindow::selectAll()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->selectAll();
    }
}

void MainWindow::find()
{
    m_findReplaceDock->show();
    m_findReplacePanel->showFindPanel();
}

void MainWindow::replace()
{
    m_findReplaceDock->show();
    m_findReplacePanel->showReplacePanel();
}

void MainWindow::zoomIn()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->zoomIn();
    }
}

void MainWindow::zoomOut()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->zoomOut();
    }
}

void MainWindow::resetZoom()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->resetZoom();
    }
}

void MainWindow::toggleWordWrap()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        QTextOption::WrapMode mode = editor->wordWrapMode() == QTextOption::NoWrap ? 
            QTextOption::WrapAtWordBoundaryOrAnywhere : QTextOption::NoWrap;
        editor->setWordWrapMode(mode);
    }
}

void MainWindow::toggleLineNumbers()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        editor->setLineNumbersVisible(!editor->lineNumbersVisible());
    }
}

void MainWindow::showPreferences()
{
    // TODO: Implement preferences dialog
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About Multi-Tab Editor"),
        tr("Multi-Tab Editor v1.0\n\n"
           "A modern text editor built with Qt 6 and C++20.\n"
           "Features multi-tab interface, syntax highlighting, "
           "and modern editing capabilities."));
}

void MainWindow::onTabChanged(int index)
{
    updateActions();
    updateWindowTitle();
    updateStatusBar();
    
    TextEditor *editor = m_tabWidget->editorAt(index);
    if (editor && m_findReplacePanel) {
        m_findReplacePanel->setTextEditor(editor);
    }
}

void MainWindow::onTabCloseRequested(int index)
{
    m_tabWidget->closeTab(index);
}

void MainWindow::onDocumentModified()
{
    updateActions();
    updateWindowTitle();
}

void MainWindow::setupUI()
{
    m_tabWidget = new TabWidget(this);
    setCentralWidget(m_tabWidget);
    
    connect(m_tabWidget, &TabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(m_tabWidget, &TabWidget::tabCloseRequested, this, &MainWindow::onTabCloseRequested);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    // File Menu
    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(m_newAction);
    fileMenu->addAction(m_openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_saveAction);
    fileMenu->addAction(m_saveAsAction);
    fileMenu->addAction(m_saveAllAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_closeTabAction);
    fileMenu->addAction(m_closeAllTabsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);
    
    // Edit Menu
    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(m_undoAction);
    editMenu->addAction(m_redoAction);
    editMenu->addSeparator();
    editMenu->addAction(m_cutAction);
    editMenu->addAction(m_copyAction);
    editMenu->addAction(m_pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(m_selectAllAction);
    editMenu->addSeparator();
    editMenu->addAction(m_findAction);
    editMenu->addAction(m_replaceAction);
    
    // View Menu
    QMenu *viewMenu = menuBar->addMenu(tr("&View"));
    viewMenu->addAction(m_zoomInAction);
    viewMenu->addAction(m_zoomOutAction);
    viewMenu->addAction(m_resetZoomAction);
    viewMenu->addSeparator();
    viewMenu->addAction(m_wordWrapAction);
    viewMenu->addAction(m_lineNumbersAction);
    
    // Help Menu
    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(m_preferencesAction);
    helpMenu->addSeparator();
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::setupToolBar()
{
    QToolBar *toolBar = addToolBar(tr("Main"));
    toolBar->addAction(m_newAction);
    toolBar->addAction(m_openAction);
    toolBar->addAction(m_saveAction);
    toolBar->addSeparator();
    toolBar->addAction(m_cutAction);
    toolBar->addAction(m_copyAction);
    toolBar->addAction(m_pasteAction);
    toolBar->addSeparator();
    toolBar->addAction(m_undoAction);
    toolBar->addAction(m_redoAction);
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::setupDockWidgets()
{
    // File Explorer
    m_fileExplorer = new FileExplorer(this);
    m_fileExplorerDock = new QDockWidget(tr("File Explorer"), this);
    m_fileExplorerDock->setWidget(m_fileExplorer);
    addDockWidget(Qt::LeftDockWidgetArea, m_fileExplorerDock);
    
    // Find/Replace Panel
    m_findReplacePanel = new FindReplacePanel(this);
    m_findReplaceDock = new QDockWidget(tr("Find and Replace"), this);
    m_findReplaceDock->setWidget(m_findReplacePanel);
    addDockWidget(Qt::BottomDockWidgetArea, m_findReplaceDock);
    m_findReplaceDock->hide();
    
    connect(m_fileExplorer, &FileExplorer::fileDoubleClicked, this, QOverload<const QString&>::of(&MainWindow::openFile));
}

void MainWindow::createActions()
{
    m_newAction = new QAction(tr("&New"), this);
    m_newAction->setShortcut(QKeySequence::New);
    m_newAction->setStatusTip(tr("Create a new file"));
    connect(m_newAction, &QAction::triggered, this, &MainWindow::newFile);
    
    m_openAction = new QAction(tr("&Open..."), this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open an existing file"));
    connect(m_openAction, &QAction::triggered, this, QOverload<>::of(&MainWindow::openFile));
    
    m_saveAction = new QAction(tr("&Save"), this);
    m_saveAction->setShortcut(QKeySequence::Save);
    m_saveAction->setStatusTip(tr("Save the document to disk"));
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    
    m_saveAsAction = new QAction(tr("Save &As..."), this);
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip(tr("Save the document under a new name"));
    connect(m_saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    
    m_saveAllAction = new QAction(tr("Save A&ll"), this);
    m_saveAllAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    m_saveAllAction->setStatusTip(tr("Save all open documents"));
    connect(m_saveAllAction, &QAction::triggered, this, &MainWindow::saveAllFiles);
    
    m_closeTabAction = new QAction(tr("&Close Tab"), this);
    m_closeTabAction->setShortcut(QKeySequence::Close);
    m_closeTabAction->setStatusTip(tr("Close the current tab"));
    connect(m_closeTabAction, &QAction::triggered, this, &MainWindow::closeTab);
    
    m_closeAllTabsAction = new QAction(tr("Close &All Tabs"), this);
    m_closeAllTabsAction->setStatusTip(tr("Close all tabs"));
    connect(m_closeAllTabsAction, &QAction::triggered, this, &MainWindow::closeAllTabs);
    
    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, &QAction::triggered, this, &MainWindow::exitApplication);
    
    m_undoAction = new QAction(tr("&Undo"), this);
    m_undoAction->setShortcut(QKeySequence::Undo);
    m_undoAction->setStatusTip(tr("Undo the last operation"));
    connect(m_undoAction, &QAction::triggered, this, &MainWindow::undo);
    
    m_redoAction = new QAction(tr("&Redo"), this);
    m_redoAction->setShortcut(QKeySequence::Redo);
    m_redoAction->setStatusTip(tr("Redo the last operation"));
    connect(m_redoAction, &QAction::triggered, this, &MainWindow::redo);
    
    m_cutAction = new QAction(tr("Cu&t"), this);
    m_cutAction->setShortcut(QKeySequence::Cut);
    m_cutAction->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(m_cutAction, &QAction::triggered, this, &MainWindow::cut);
    
    m_copyAction = new QAction(tr("&Copy"), this);
    m_copyAction->setShortcut(QKeySequence::Copy);
    m_copyAction->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(m_copyAction, &QAction::triggered, this, &MainWindow::copy);
    
    m_pasteAction = new QAction(tr("&Paste"), this);
    m_pasteAction->setShortcut(QKeySequence::Paste);
    m_pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(m_pasteAction, &QAction::triggered, this, &MainWindow::paste);
    
    m_selectAllAction = new QAction(tr("Select &All"), this);
    m_selectAllAction->setShortcut(QKeySequence::SelectAll);
    m_selectAllAction->setStatusTip(tr("Select all text"));
    connect(m_selectAllAction, &QAction::triggered, this, &MainWindow::selectAll);
    
    m_findAction = new QAction(tr("&Find..."), this);
    m_findAction->setShortcut(QKeySequence::Find);
    m_findAction->setStatusTip(tr("Find text"));
    connect(m_findAction, &QAction::triggered, this, &MainWindow::find);
    
    m_replaceAction = new QAction(tr("&Replace..."), this);
    m_replaceAction->setShortcut(QKeySequence::Replace);
    m_replaceAction->setStatusTip(tr("Find and replace text"));
    connect(m_replaceAction, &QAction::triggered, this, &MainWindow::replace);
    
    m_zoomInAction = new QAction(tr("Zoom &In"), this);
    m_zoomInAction->setShortcut(QKeySequence::ZoomIn);
    m_zoomInAction->setStatusTip(tr("Zoom in"));
    connect(m_zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    
    m_zoomOutAction = new QAction(tr("Zoom &Out"), this);
    m_zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    m_zoomOutAction->setStatusTip(tr("Zoom out"));
    connect(m_zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    
    m_resetZoomAction = new QAction(tr("&Reset Zoom"), this);
    m_resetZoomAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    m_resetZoomAction->setStatusTip(tr("Reset zoom to default"));
    connect(m_resetZoomAction, &QAction::triggered, this, &MainWindow::resetZoom);
    
    m_wordWrapAction = new QAction(tr("&Word Wrap"), this);
    m_wordWrapAction->setCheckable(true);
    m_wordWrapAction->setStatusTip(tr("Toggle word wrap"));
    connect(m_wordWrapAction, &QAction::triggered, this, &MainWindow::toggleWordWrap);
    
    m_lineNumbersAction = new QAction(tr("&Line Numbers"), this);
    m_lineNumbersAction->setCheckable(true);
    m_lineNumbersAction->setChecked(true);
    m_lineNumbersAction->setStatusTip(tr("Toggle line numbers"));
    connect(m_lineNumbersAction, &QAction::triggered, this, &MainWindow::toggleLineNumbers);
    
    m_preferencesAction = new QAction(tr("&Preferences..."), this);
    m_preferencesAction->setStatusTip(tr("Open preferences dialog"));
    connect(m_preferencesAction, &QAction::triggered, this, &MainWindow::showPreferences);
    
    m_aboutAction = new QAction(tr("&About"), this);
    m_aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::updateActions()
{
    bool hasEditor = m_tabWidget->currentEditor() != nullptr;
    bool hasSelection = false;
    bool canUndo = false;
    bool canRedo = false;
    
    if (hasEditor) {
        TextEditor *editor = m_tabWidget->currentEditor();
        hasSelection = editor->textCursor().hasSelection();
        canUndo = editor->document()->isUndoAvailable();
        canRedo = editor->document()->isRedoAvailable();
    }
    
    m_saveAction->setEnabled(hasEditor);
    m_saveAsAction->setEnabled(hasEditor);
    m_closeTabAction->setEnabled(hasEditor);
    
    m_undoAction->setEnabled(canUndo);
    m_redoAction->setEnabled(canRedo);
    m_cutAction->setEnabled(hasSelection);
    m_copyAction->setEnabled(hasSelection);
    m_pasteAction->setEnabled(hasEditor);
    m_selectAllAction->setEnabled(hasEditor);
    
    m_findAction->setEnabled(hasEditor);
    m_replaceAction->setEnabled(hasEditor);
    m_zoomInAction->setEnabled(hasEditor);
    m_zoomOutAction->setEnabled(hasEditor);
    m_resetZoomAction->setEnabled(hasEditor);
    m_wordWrapAction->setEnabled(hasEditor);
    m_lineNumbersAction->setEnabled(hasEditor);
    
    m_saveAllAction->setEnabled(m_tabWidget->hasUnsavedChanges());
    m_closeAllTabsAction->setEnabled(m_tabWidget->count() > 0);
}

void MainWindow::updateWindowTitle()
{
    QString title = "Multi-Tab Editor";
    TextEditor *editor = m_tabWidget->currentEditor();
    
    if (editor) {
        QString fileName = editor->filePath().isEmpty() ? "Untitled" : QFileInfo(editor->filePath()).fileName();
        if (editor->isModified()) {
            fileName += " *";
        }
        title = fileName + " - " + title;
    }
    
    setWindowTitle(title);
}

void MainWindow::updateStatusBar()
{
    TextEditor *editor = m_tabWidget->currentEditor();
    if (editor) {
        QTextCursor cursor = editor->textCursor();
        int line = cursor.blockNumber() + 1;
        int column = cursor.columnNumber() + 1;
        statusBar()->showMessage(tr("Line %1, Column %2").arg(line).arg(column));
    } else {
        statusBar()->showMessage(tr("Ready"));
    }
}

bool MainWindow::maybeSave()
{
    if (m_tabWidget->hasUnsavedChanges()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Multi-Tab Editor"),
            tr("The document has been modified.\n"
               "Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (ret == QMessageBox::Save) {
            saveAllFiles();
            return !m_tabWidget->hasUnsavedChanges();
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveDocument(int index)
{
    TextEditor *editor = m_tabWidget->editorAt(index);
    if (!editor) return false;
    
    if (editor->filePath().isEmpty()) {
        return false;
    }
    
    QFile file(editor->filePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Multi-Tab Editor"),
            tr("Cannot write file %1:\n%2").arg(editor->filePath(), file.errorString()));
        return false;
    }
    
    QTextStream out(&file);
    out << editor->toPlainText();
    
    editor->setModified(false);
    m_tabWidget->setTabModified(index, false);
    
    m_settingsManager->addRecentFile(editor->filePath());
    
    return true;
}

void MainWindow::loadSettings()
{
    restoreGeometry(m_settingsManager->loadWindowGeometry());
    restoreState(m_settingsManager->loadWindowState());
}

void MainWindow::saveSettings()
{
    m_settingsManager->saveWindowGeometry(saveGeometry());
    m_settingsManager->saveWindowState(saveState());
}

