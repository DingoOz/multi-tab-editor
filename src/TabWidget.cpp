#include "TabWidget.h"
#include "TextEditor.h"

#include <QTabBar>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QContextMenuEvent>

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_contextMenu(nullptr)
    , m_closeTabAction(nullptr)
    , m_closeOtherTabsAction(nullptr)
    , m_closeTabsToRightAction(nullptr)
    , m_contextMenuIndex(-1)
{
    setupTabWidget();
}

TabWidget::~TabWidget()
{
}

void TabWidget::setupTabWidget()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);
    setAcceptDrops(true);
    
    // Context menu
    m_contextMenu = new QMenu(this);
    m_closeTabAction = new QAction(tr("Close Tab"), this);
    m_closeOtherTabsAction = new QAction(tr("Close Other Tabs"), this);
    m_closeTabsToRightAction = new QAction(tr("Close Tabs to the Right"), this);
    
    m_contextMenu->addAction(m_closeTabAction);
    m_contextMenu->addAction(m_closeOtherTabsAction);
    m_contextMenu->addAction(m_closeTabsToRightAction);
    
    connect(m_closeTabAction, &QAction::triggered, this, &TabWidget::closeCurrentTab);
    connect(m_closeOtherTabsAction, &QAction::triggered, this, &TabWidget::closeOtherTabs);
    connect(m_closeTabsToRightAction, &QAction::triggered, this, &TabWidget::closeTabsToTheRight);
    
    connect(this, &QTabWidget::currentChanged, this, &TabWidget::onCurrentChanged);
    connect(tabBar(), &QTabBar::tabBarDoubleClicked, this, &TabWidget::onTabBarDoubleClicked);
}

int TabWidget::addTab(TextEditor *editor, const QString &label)
{
    int index = QTabWidget::addTab(editor, label);
    
    connect(editor, &TextEditor::modificationChanged, this, &TabWidget::onDocumentModified);
    
    return index;
}

TextEditor *TabWidget::currentEditor() const
{
    return qobject_cast<TextEditor*>(currentWidget());
}

TextEditor *TabWidget::editorAt(int index) const
{
    return qobject_cast<TextEditor*>(widget(index));
}

bool TabWidget::closeTab(int index)
{
    if (index < 0 || index >= count()) {
        return false;
    }
    
    TextEditor *editor = editorAt(index);
    if (!editor) {
        return false;
    }
    
    if (editor->isModified()) {
        setCurrentIndex(index);
        QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Close Tab"),
            tr("The document has been modified.\n"
               "Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        
        if (ret == QMessageBox::Save) {
            // Signal parent to save
            emit tabCloseRequested(index);
            return false; // Let parent handle saving and closing
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    
    removeTab(index);
    editor->deleteLater();
    
    return true;
}

void TabWidget::closeAllTabs()
{
    while (count() > 0) {
        if (!closeTab(0)) {
            break; // User cancelled or error occurred
        }
    }
}

bool TabWidget::hasUnsavedChanges() const
{
    for (int i = 0; i < count(); ++i) {
        TextEditor *editor = editorAt(i);
        if (editor && editor->isModified()) {
            return true;
        }
    }
    return false;
}

void TabWidget::setTabModified(int index, bool modified)
{
    if (index < 0 || index >= count()) {
        return;
    }
    
    TextEditor *editor = editorAt(index);
    if (editor) {
        editor->setModified(modified);
        updateTabTitle(index);
    }
}

bool TabWidget::isTabModified(int index) const
{
    TextEditor *editor = editorAt(index);
    return editor ? editor->isModified() : false;
}

void TabWidget::onDocumentModified()
{
    TextEditor *editor = qobject_cast<TextEditor*>(sender());
    if (!editor) return;
    
    int index = indexOf(editor);
    if (index >= 0) {
        updateTabTitle(index);
    }
}

void TabWidget::updateTabTitle(int index)
{
    if (index < 0 || index >= count()) {
        return;
    }
    
    TextEditor *editor = editorAt(index);
    if (!editor) return;
    
    QString title = getTabTitle(editor->filePath(), editor->isModified());
    setTabText(index, title);
}

QString TabWidget::getTabTitle(const QString &filePath, bool modified)
{
    QString title;
    if (filePath.isEmpty()) {
        title = "Untitled";
    } else {
        title = QFileInfo(filePath).fileName();
    }
    
    if (modified) {
        title += " *";
    }
    
    return title;
}

void TabWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        QTabWidget::dragEnterEvent(event);
    }
}

void TabWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        const QList<QUrl> urls = event->mimeData()->urls();
        for (const QUrl &url : urls) {
            if (url.isLocalFile()) {
                QString filePath = url.toLocalFile();
                // Signal parent to open file
                emit currentEditorChanged(nullptr); // Placeholder signal for file opening
            }
        }
        event->acceptProposedAction();
    } else {
        QTabWidget::dropEvent(event);
    }
}

void TabWidget::contextMenuEvent(QContextMenuEvent *event)
{
    int index = tabBar()->tabAt(event->pos());
    if (index >= 0) {
        m_contextMenuIndex = index;
        
        m_closeOtherTabsAction->setEnabled(count() > 1);
        m_closeTabsToRightAction->setEnabled(index < count() - 1);
        
        m_contextMenu->exec(event->globalPos());
    }
}

void TabWidget::onCurrentChanged(int index)
{
    TextEditor *editor = editorAt(index);
    emit currentEditorChanged(editor);
}

void TabWidget::onTabBarDoubleClicked(int index)
{
    // Double-click on empty area creates new tab
    if (index == -1) {
        emit currentEditorChanged(nullptr); // Signal for new file
    }
}

void TabWidget::closeCurrentTab()
{
    if (m_contextMenuIndex >= 0) {
        closeTab(m_contextMenuIndex);
    }
}

void TabWidget::closeOtherTabs()
{
    if (m_contextMenuIndex < 0) return;
    
    // Close tabs after the context menu tab
    while (count() > m_contextMenuIndex + 1) {
        if (!closeTab(count() - 1)) {
            break;
        }
    }
    
    // Close tabs before the context menu tab
    while (m_contextMenuIndex > 0) {
        if (!closeTab(0)) {
            break;
        }
        m_contextMenuIndex--; // Adjust index as tabs are removed
    }
}

void TabWidget::closeTabsToTheRight()
{
    if (m_contextMenuIndex < 0) return;
    
    while (count() > m_contextMenuIndex + 1) {
        if (!closeTab(count() - 1)) {
            break;
        }
    }
}

