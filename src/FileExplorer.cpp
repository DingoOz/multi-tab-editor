#include "FileExplorer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QStandardPaths>

FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
    , m_treeView(nullptr)
    , m_fileSystemModel(nullptr)
    , m_pathEdit(nullptr)
    , m_browseButton(nullptr)
    , m_contextMenu(nullptr)
    , m_newFileAction(nullptr)
    , m_newFolderAction(nullptr)
    , m_deleteAction(nullptr)
    , m_renameAction(nullptr)
    , m_copyPathAction(nullptr)
    , m_revealAction(nullptr)
    , m_currentPath()
{
    setupUI();
    setupContextMenu();
    
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    setRootPath(homeDir);
}

FileExplorer::~FileExplorer()
{
}

void FileExplorer::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);
    
    // Path bar
    QHBoxLayout *pathLayout = new QHBoxLayout();
    m_pathEdit = new QLineEdit(this);
    m_pathEdit->setReadOnly(true);
    m_browseButton = new QPushButton("...", this);
    m_browseButton->setMaximumWidth(30);
    m_browseButton->setToolTip(tr("Browse for folder"));
    
    pathLayout->addWidget(m_pathEdit);
    pathLayout->addWidget(m_browseButton);
    
    // Tree view
    m_treeView = new QTreeView(this);
    m_fileSystemModel = new QFileSystemModel(this);
    m_fileSystemModel->setRootPath("");
    
    m_treeView->setModel(m_fileSystemModel);
    m_treeView->setRootIndex(m_fileSystemModel->index(QDir::currentPath()));
    
    // Hide size, type, and date columns
    m_treeView->hideColumn(1);
    m_treeView->hideColumn(2);
    m_treeView->hideColumn(3);
    
    m_treeView->setHeaderHidden(true);
    m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    
    layout->addLayout(pathLayout);
    layout->addWidget(m_treeView);
    
    // Connections
    connect(m_browseButton, &QPushButton::clicked, this, &FileExplorer::browseFolder);
    connect(m_treeView, &QTreeView::doubleClicked, this, &FileExplorer::onItemDoubleClicked);
    connect(m_treeView, &QTreeView::clicked, this, &FileExplorer::onItemClicked);
    connect(m_treeView, &QTreeView::customContextMenuRequested, this, &FileExplorer::onCustomContextMenuRequested);
}

void FileExplorer::setupContextMenu()
{
    m_contextMenu = new QMenu(this);
    
    m_newFileAction = new QAction(tr("New File"), this);
    m_newFolderAction = new QAction(tr("New Folder"), this);
    m_deleteAction = new QAction(tr("Delete"), this);
    m_renameAction = new QAction(tr("Rename"), this);
    m_copyPathAction = new QAction(tr("Copy Path"), this);
    m_revealAction = new QAction(tr("Reveal in File Manager"), this);
    
    m_contextMenu->addAction(m_newFileAction);
    m_contextMenu->addAction(m_newFolderAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_renameAction);
    m_contextMenu->addAction(m_deleteAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_copyPathAction);
    m_contextMenu->addAction(m_revealAction);
    
    connect(m_newFileAction, &QAction::triggered, this, &FileExplorer::createNewFile);
    connect(m_newFolderAction, &QAction::triggered, this, &FileExplorer::createNewFolder);
    connect(m_deleteAction, &QAction::triggered, this, &FileExplorer::deleteItem);
    connect(m_renameAction, &QAction::triggered, this, &FileExplorer::renameItem);
    connect(m_copyPathAction, &QAction::triggered, this, &FileExplorer::copyPath);
    connect(m_revealAction, &QAction::triggered, this, &FileExplorer::revealInSystem);
}

void FileExplorer::setRootPath(const QString &path)
{
    QDir dir(path);
    if (dir.exists()) {
        m_currentPath = dir.absolutePath();
        m_pathEdit->setText(m_currentPath);
        m_treeView->setRootIndex(m_fileSystemModel->index(m_currentPath));
    }
}

QString FileExplorer::rootPath() const
{
    return m_currentPath;
}

void FileExplorer::refresh()
{
    // QFileSystemModel automatically refreshes in Qt6
    // Force refresh by setting the root path again
    QString currentPath = m_currentPath;
    setRootPath(currentPath);
}

void FileExplorer::onItemDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    
    QString filePath = m_fileSystemModel->filePath(index);
    QFileInfo fileInfo(filePath);
    
    if (fileInfo.isFile() && isValidTextFile(filePath)) {
        emit fileDoubleClicked(filePath);
    }
}

void FileExplorer::onItemClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    
    QString filePath = m_fileSystemModel->filePath(index);
    emit fileSelected(filePath);
}

void FileExplorer::onCustomContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = m_treeView->indexAt(pos);
    updateActions();
    
    if (index.isValid()) {
        QString filePath = m_fileSystemModel->filePath(index);
        QFileInfo fileInfo(filePath);
        
        m_deleteAction->setEnabled(true);
        m_renameAction->setEnabled(true);
        m_copyPathAction->setEnabled(true);
        m_revealAction->setEnabled(true);
    } else {
        m_deleteAction->setEnabled(false);
        m_renameAction->setEnabled(false);
        m_copyPathAction->setEnabled(false);
        m_revealAction->setEnabled(false);
    }
    
    m_contextMenu->exec(m_treeView->mapToGlobal(pos));
}

void FileExplorer::browseFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), m_currentPath);
    if (!dir.isEmpty()) {
        setRootPath(dir);
    }
}

void FileExplorer::createNewFile()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("New File"), 
                                           tr("File name:"), QLineEdit::Normal, 
                                           "untitled.txt", &ok);
    if (ok && !fileName.isEmpty()) {
        QString fullPath = QDir(m_currentPath).filePath(fileName);
        QFile file(fullPath);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
            refresh();
            emit fileDoubleClicked(fullPath);
        } else {
            QMessageBox::warning(this, tr("Error"), 
                               tr("Could not create file: %1").arg(fileName));
        }
    }
}

void FileExplorer::createNewFolder()
{
    bool ok;
    QString folderName = QInputDialog::getText(this, tr("New Folder"), 
                                             tr("Folder name:"), QLineEdit::Normal, 
                                             "New Folder", &ok);
    if (ok && !folderName.isEmpty()) {
        QDir dir(m_currentPath);
        if (dir.mkdir(folderName)) {
            refresh();
        } else {
            QMessageBox::warning(this, tr("Error"), 
                               tr("Could not create folder: %1").arg(folderName));
        }
    }
}

void FileExplorer::deleteItem()
{
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return;
    
    QString filePath = m_fileSystemModel->filePath(index);
    QFileInfo fileInfo(filePath);
    
    QString message;
    if (fileInfo.isDir()) {
        message = tr("Are you sure you want to delete the folder '%1'?").arg(fileInfo.fileName());
    } else {
        message = tr("Are you sure you want to delete the file '%1'?").arg(fileInfo.fileName());
    }
    
    QMessageBox::StandardButton ret = QMessageBox::question(this, tr("Delete"), message,
                                                           QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        if (fileInfo.isDir()) {
            QDir dir(filePath);
            if (!dir.removeRecursively()) {
                QMessageBox::warning(this, tr("Error"), 
                                   tr("Could not delete folder: %1").arg(fileInfo.fileName()));
            }
        } else {
            QFile file(filePath);
            if (!file.remove()) {
                QMessageBox::warning(this, tr("Error"), 
                                   tr("Could not delete file: %1").arg(fileInfo.fileName()));
            }
        }
        refresh();
    }
}

void FileExplorer::renameItem()
{
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return;
    
    QString filePath = m_fileSystemModel->filePath(index);
    QFileInfo fileInfo(filePath);
    
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Rename"), 
                                          tr("New name:"), QLineEdit::Normal, 
                                          fileInfo.fileName(), &ok);
    
    if (ok && !newName.isEmpty() && newName != fileInfo.fileName()) {
        QString newPath = QDir(fileInfo.absolutePath()).filePath(newName);
        QFile file(filePath);
        if (!file.rename(newPath)) {
            QMessageBox::warning(this, tr("Error"), 
                               tr("Could not rename: %1").arg(fileInfo.fileName()));
        } else {
            refresh();
        }
    }
}

void FileExplorer::copyPath()
{
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return;
    
    QString filePath = m_fileSystemModel->filePath(index);
    QApplication::clipboard()->setText(filePath);
}

void FileExplorer::revealInSystem()
{
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return;
    
    QString filePath = m_fileSystemModel->filePath(index);
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(filePath).absolutePath()));
}

void FileExplorer::updateActions()
{
    // Actions are always enabled in current implementation
    // This method is here for future enhancements
}

bool FileExplorer::isValidTextFile(const QString &filePath) const
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();
    
    // List of supported text file extensions
    QStringList textExtensions = {
        "txt", "cpp", "c", "h", "hpp", "cxx", "cc",
        "py", "js", "ts", "json", "xml", "html", "htm",
        "css", "scss", "less", "md", "rst", "yaml", "yml",
        "ini", "cfg", "conf", "log", "csv", "tsv"
    };
    
    return textExtensions.contains(suffix) || suffix.isEmpty();
}

