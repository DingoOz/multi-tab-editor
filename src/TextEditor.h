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

class TextEditor : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    void setFilePath(const QString &filePath);
    QString filePath() const;
    
    void setLanguage(const QString &language);
    QString language() const;
    
    bool isModified() const;
    void setModified(bool modified);
    
    void setLineNumbersVisible(bool visible);
    bool lineNumbersVisible() const;
    
    void setWordWrapMode(QTextOption::WrapMode mode);
    
    void zoomIn(int range = 1);
    void zoomOut(int range = 1);
    void resetZoom();
    
    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent *event);

public slots:
    void highlightCurrentLine();
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void onFileChanged(const QString &path);

signals:
    void modificationChanged(bool changed);
    void cursorPositionChanged(int line, int column);
    void fileChangedExternally(const QString &filePath);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onCursorPositionChanged();
    void onTextChanged();

private:
    void setupEditor();
    void setupSyntaxHighlighter();
    void autoIndent();
    void matchBrackets();
    bool handleTabIndentation(QKeyEvent *event);
    
    QString m_filePath;
    QString m_language;
    bool m_modified;
    bool m_lineNumbersVisible;
    int m_baseZoomLevel;
    
    LineNumberArea *m_lineNumberArea;
    SyntaxHighlighter *m_syntaxHighlighter;
    QCompleter *m_completer;
    QTimer *m_cursorTimer;
    QFileSystemWatcher *m_fileWatcher;
    QDateTime m_lastModified;
};

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(TextEditor *editor) : QWidget(editor), m_textEditor(editor) {}

    QSize sizeHint() const override
    {
        return QSize(m_textEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        m_textEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TextEditor *m_textEditor;
};