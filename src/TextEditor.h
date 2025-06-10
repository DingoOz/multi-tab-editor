/**
 * @file TextEditor.h
 * @brief Enhanced text editor widget with line numbers and advanced features
 * @author Multi-Tab Editor Team
 * @date 2025
 */

#pragma once

#include <QTextEdit>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QMenu>
#include <QContextMenuEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <memory>

class SyntaxHighlighter;
class QCompleter;

class LineNumberArea;

/**
 * @class TextEditor
 * @brief Enhanced text editing widget with line numbers and advanced features
 * 
 * TextEditor extends QTextEdit to provide:
 * - Line number display with auto-sizing
 * - Syntax highlighting for multiple languages
 * - File change detection and monitoring
 * - Auto-indentation and bracket matching
 * - Zoom functionality with keyboard shortcuts
 * - Current line highlighting
 * - Context menu enhancements
 * 
 * The editor supports file association, modification tracking, and integrates
 * with the application's syntax highlighting system.
 * 
 * @see SyntaxHighlighter, LineNumberArea
 */
class TextEditor : public QTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a text editor widget
     * @param parent Parent widget (typically MainWindow or TabWidget)
     * 
     * Initializes the editor with line numbers, syntax highlighting,
     * and file monitoring capabilities.
     */
    explicit TextEditor(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor - cleans up resources and file watchers
     */
    ~TextEditor();

    /**
     * @brief Sets the file path for this editor
     * @param filePath Full path to the associated file
     * 
     * Updates the file path, sets up file monitoring, and updates
     * syntax highlighting based on file extension.
     */
    void setFilePath(const QString &filePath);
    
    /**
     * @brief Gets the current file path
     * @return Full path to associated file, or empty if untitled
     */
    QString filePath() const;
    
    /**
     * @brief Sets the programming language for syntax highlighting
     * @param language Language identifier (e.g., "cpp", "python", "javascript")
     */
    void setLanguage(const QString &language);
    
    /**
     * @brief Gets the current language setting
     * @return Language identifier for syntax highlighting
     */
    QString language() const;
    
    /**
     * @brief Checks if the document has been modified
     * @return true if document has unsaved changes
     */
    bool isModified() const;
    
    /**
     * @brief Sets the modification state of the document
     * @param modified true to mark as modified, false for saved state
     * 
     * Emits modificationChanged signal when state changes.
     */
    void setModified(bool modified);
    
    /**
     * @brief Shows or hides line numbers
     * @param visible true to show line numbers, false to hide
     */
    void setLineNumbersVisible(bool visible);
    
    /**
     * @brief Gets line number visibility state
     * @return true if line numbers are visible
     */
    bool lineNumbersVisible() const;
    
    /**
     * @brief Sets word wrap mode for the editor
     * @param mode Word wrap mode (NoWrap, WrapAtWordBoundaryOrAnywhere, etc.)
     */
    void setWordWrapMode(QTextOption::WrapMode mode);
    
    /**
     * @brief Increases font size for zoom in
     * @param range Number of steps to zoom in (default 1)
     */
    void zoomIn(int range = 1);
    
    /**
     * @brief Decreases font size for zoom out
     * @param range Number of steps to zoom out (default 1)
     */
    void zoomOut(int range = 1);
    
    /**
     * @brief Resets zoom to default font size
     */
    void resetZoom();
    
    /**
     * @brief Calculates required width for line number area
     * @return Width in pixels needed for line number display
     */
    int lineNumberAreaWidth();
    
    /**
     * @brief Handles paint events for the line number area
     * @param event Paint event containing drawing region
     * 
     * Called by LineNumberArea widget to draw line numbers.
     */
    void lineNumberAreaPaintEvent(QPaintEvent *event);

public slots:
    /** @brief Highlights the current line with background color */
    void highlightCurrentLine();
    
    /**
     * @brief Updates line number area width when block count changes
     * @param newBlockCount New number of text blocks in document
     */
    void updateLineNumberAreaWidth(int newBlockCount);
    
    /**
     * @brief Updates line number area when text scrolls or changes
     * @param rect Rectangle area that needs updating
     * @param dy Vertical scroll offset
     */
    void updateLineNumberArea(const QRect &rect, int dy);
    
    /**
     * @brief Handles file system change notifications
     * @param path Path of the file that changed
     */
    void onFileChanged(const QString &path);

signals:
    /**
     * @brief Emitted when document modification state changes
     * @param changed true if document is now modified, false if saved
     */
    void modificationChanged(bool changed);
    
    /**
     * @brief Emitted when cursor position changes
     * @param line Current line number (1-based)
     * @param column Current column number (1-based)
     */
    void cursorPositionChanged(int line, int column);
    
    /**
     * @brief Emitted when associated file is modified externally
     * @param filePath Path of the file that was modified
     */
    void fileChangedExternally(const QString &filePath);

protected:
    /**
     * @brief Handles right-click context menu events
     * @param event Context menu event
     */
    void contextMenuEvent(QContextMenuEvent *event) override;
    
    /**
     * @brief Handles keyboard input with auto-indentation and shortcuts
     * @param event Key press event
     */
    void keyPressEvent(QKeyEvent *event) override;
    
    /**
     * @brief Handles mouse wheel events for zoom functionality
     * @param event Wheel event
     */
    void wheelEvent(QWheelEvent *event) override;
    
    /**
     * @brief Handles widget resize events for line number area
     * @param event Resize event
     */
    void resizeEvent(QResizeEvent *event) override;

private slots:
    /** @brief Internal handler for cursor position changes */
    void onCursorPositionChanged();
    
    /** @brief Internal handler for text content changes */
    void onTextChanged();

private:
    /** @brief Sets up editor configuration and connections */
    void setupEditor();
    
    /** @brief Initializes syntax highlighter based on file type */
    void setupSyntaxHighlighter();
    
    /** @brief Performs automatic indentation on new lines */
    void autoIndent();
    
    /** @brief Highlights matching brackets/parentheses */
    void matchBrackets();
    
    /**
     * @brief Handles tab key for indentation
     * @param event Key event for tab press
     * @return true if tab was handled, false for default behavior
     */
    bool handleTabIndentation(QKeyEvent *event);
    
    // File Association
    /** @brief Full path to associated file (empty for untitled documents) */
    QString m_filePath;
    
    /** @brief Programming language for syntax highlighting */
    QString m_language;
    
    /** @brief Whether document has been modified since last save */
    bool m_modified;
    
    /** @brief Whether line numbers are currently visible */
    bool m_lineNumbersVisible;
    
    /** @brief Base zoom level for font size calculations */
    int m_baseZoomLevel;
    
    // UI Components
    /** @brief Widget for displaying line numbers */
    LineNumberArea *m_lineNumberArea;
    
    /** @brief Syntax highlighter for code coloring */
    SyntaxHighlighter *m_syntaxHighlighter;
    
    /** @brief Auto-completion provider (future enhancement) */
    QCompleter *m_completer;
    
    /** @brief Timer for cursor-related updates */
    QTimer *m_cursorTimer;
    
    /** @brief File system watcher for external change detection */
    QFileSystemWatcher *m_fileWatcher;
    
    /** @brief Last modification time for change detection */
    QDateTime m_lastModified;
};

/**
 * @class LineNumberArea
 * @brief Widget for displaying line numbers alongside text editor
 * 
 * LineNumberArea is a simple widget that displays line numbers
 * for the associated TextEditor. It automatically sizes itself
 * based on the number of lines and delegates all painting to
 * the TextEditor.
 * 
 * @see TextEditor
 */
class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs line number area for given editor
     * @param editor TextEditor that this line number area serves
     */
    LineNumberArea(TextEditor *editor) : QWidget(editor), m_textEditor(editor) {}

    /**
     * @brief Provides size hint for layout management
     * @return Preferred size based on line number width
     */
    QSize sizeHint() const override
    {
        return QSize(m_textEditor->lineNumberAreaWidth(), 0);
    }

protected:
    /**
     * @brief Handles paint events by delegating to TextEditor
     * @param event Paint event to handle
     */
    void paintEvent(QPaintEvent *event) override
    {
        m_textEditor->lineNumberAreaPaintEvent(event);
    }

private:
    /** @brief Pointer to associated text editor */
    TextEditor *m_textEditor;
};