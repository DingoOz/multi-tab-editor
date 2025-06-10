#pragma once

#include <QWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QModelIndex>
#include <QDir>

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorer(QWidget *parent = nullptr);
    ~FileExplorer();

    void setRootPath(const QString &path);
    QString rootPath() const;
    
    void refresh();

signals:
    void fileDoubleClicked(const QString &filePath);
    void fileSelected(const QString &filePath);

private slots:
    void onItemDoubleClicked(const QModelIndex &index);
    void onItemClicked(const QModelIndex &index);
    void onCustomContextMenuRequested(const QPoint &pos);
    void browseFolder();
    void createNewFile();
    void createNewFolder();
    void deleteItem();
    void renameItem();
    void copyPath();
    void revealInSystem();

private:
    void setupUI();
    void setupContextMenu();
    void updateActions();
    bool isValidTextFile(const QString &filePath) const;
    
    QTreeView *m_treeView;
    QFileSystemModel *m_fileSystemModel;
    QLineEdit *m_pathEdit;
    QPushButton *m_browseButton;
    
    QMenu *m_contextMenu;
    QAction *m_newFileAction;
    QAction *m_newFolderAction;
    QAction *m_deleteAction;
    QAction *m_renameAction;
    QAction *m_copyPathAction;
    QAction *m_revealAction;
    
    QString m_currentPath;
};