/**
 * @file TabWidget.h
 * @brief Enhanced tab widget for managing multiple text editors
 * @author Multi-Tab Editor Team
 * @date 2025
 */

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

/**
 * @class TabWidget
 * @brief Enhanced tab widget for managing multiple text editor instances
 * 
 * TabWidget extends QTabWidget to provide advanced tab management features:
 * - Drag and drop support for opening files
 * - Context menu with tab operations (close, close others, etc.)
 * - Modified state tracking with visual indicators
 * - Smart tab closing with unsaved change handling
 * - Double-click actions on tabs and tab bar
 * 
 * Each tab contains a TextEditor instance and maintains state information
 * about file modifications, making it easy to track unsaved changes
 * across all open documents.
 * 
 * @see TextEditor, MainWindow
 */
class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a tab widget for managing text editors
     * @param parent Parent widget (typically MainWindow)
     */
    explicit TabWidget(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor - ensures proper cleanup of tabs
     */
    ~TabWidget();

    /**
     * @brief Adds a new tab with a text editor
     * @param editor TextEditor instance to add to the tab
     * @param label Initial tab label/title
     * @return Index of the newly added tab
     */
    int addTab(TextEditor *editor, const QString &label);
    
    /**
     * @brief Gets the currently active text editor
     * @return Pointer to current TextEditor, or nullptr if no tabs open
     */
    TextEditor *currentEditor() const;
    
    /**
     * @brief Gets text editor at specific tab index
     * @param index Tab index to query
     * @return Pointer to TextEditor at index, or nullptr if invalid
     */
    TextEditor *editorAt(int index) const;
    
    /**
     * @brief Closes tab at specified index with unsaved change handling
     * @param index Index of tab to close
     * @return true if tab was closed, false if user cancelled
     */
    bool closeTab(int index);
    
    /**
     * @brief Closes all open tabs with unsaved change handling
     */
    void closeAllTabs();
    
    /**
     * @brief Checks if any tab has unsaved changes
     * @return true if any editor has modifications
     */
    bool hasUnsavedChanges() const;
    
    /**
     * @brief Sets the modification state of a tab
     * @param index Tab index to modify
     * @param modified true to mark as modified (shows asterisk in title)
     */
    void setTabModified(int index, bool modified);
    
    /**
     * @brief Checks if a tab has unsaved modifications
     * @param index Tab index to check
     * @return true if tab is marked as modified
     */
    bool isTabModified(int index) const;

public slots:
    /**
     * @brief Handles document modification events from editors
     * 
     * Connected to TextEditor modification signals to update tab titles.
     */
    void onDocumentModified();
    
    /**
     * @brief Updates tab title for specified index
     * @param index Tab index to update
     */
    void updateTabTitle(int index);

signals:
    /**
     * @brief Emitted when a tab close is requested
     * @param index Index of tab requesting to be closed
     */
    void tabCloseRequested(int index);
    
    /**
     * @brief Emitted when the current editor changes
     * @param editor Pointer to the new current editor
     */
    void currentEditorChanged(TextEditor *editor);

protected:
    /**
     * @brief Handles drag enter events for file dropping
     * @param event Drag enter event
     * 
     * Accepts file drops to open files in new tabs.
     */
    void dragEnterEvent(QDragEnterEvent *event) override;
    
    /**
     * @brief Handles drop events for opening dragged files
     * @param event Drop event containing file URLs
     */
    void dropEvent(QDropEvent *event) override;
    
    /**
     * @brief Shows context menu on right-click
     * @param event Context menu event
     */
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    /**
     * @brief Internal handler for current tab changes
     * @param index New current tab index
     */
    void onCurrentChanged(int index);
    
    /**
     * @brief Handles double-click on tab bar
     * @param index Tab index that was double-clicked
     */
    void onTabBarDoubleClicked(int index);
    
    /** @brief Closes the currently active tab */
    void closeCurrentTab();
    
    /** @brief Closes all tabs except the current one */
    void closeOtherTabs();
    
    /** @brief Closes all tabs to the right of the current one */
    void closeTabsToTheRight();

private:
    /** @brief Sets up tab widget configuration and connections */
    void setupTabWidget();
    
    /**
     * @brief Generates appropriate tab title from file path
     * @param filePath Full file path or empty for untitled
     * @param modified Whether to show modification indicator
     * @return Formatted tab title
     */
    QString getTabTitle(const QString &filePath, bool modified = false);
    
    // Context Menu Components
    /** @brief Right-click context menu for tabs */
    QMenu *m_contextMenu;
    
    /** @brief Action to close the clicked tab */
    QAction *m_closeTabAction;
    
    /** @brief Action to close all other tabs */
    QAction *m_closeOtherTabsAction;
    
    /** @brief Action to close tabs to the right */
    QAction *m_closeTabsToRightAction;
    
    /** @brief Index of tab where context menu was opened */
    int m_contextMenuIndex;
};