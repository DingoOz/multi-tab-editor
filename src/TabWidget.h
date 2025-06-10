#pragma once

#include <QTabWidget>
#include <QTabBar>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QMenu>
#include <QAction>

class TextEditor;

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    ~TabWidget();

    int addTab(TextEditor *editor, const QString &label);
    TextEditor *currentEditor() const;
    TextEditor *editorAt(int index) const;
    
    bool closeTab(int index);
    void closeAllTabs();
    bool hasUnsavedChanges() const;
    
    void setTabModified(int index, bool modified);
    bool isTabModified(int index) const;

public slots:
    void onDocumentModified();
    void updateTabTitle(int index);

signals:
    void tabCloseRequested(int index);
    void currentEditorChanged(TextEditor *editor);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void onCurrentChanged(int index);
    void onTabBarDoubleClicked(int index);
    void closeCurrentTab();
    void closeOtherTabs();
    void closeTabsToTheRight();

private:
    void setupTabWidget();
    QString getTabTitle(const QString &filePath, bool modified = false);
    
    QMenu *m_contextMenu;
    QAction *m_closeTabAction;
    QAction *m_closeOtherTabsAction;
    QAction *m_closeTabsToRightAction;
    int m_contextMenuIndex;
};