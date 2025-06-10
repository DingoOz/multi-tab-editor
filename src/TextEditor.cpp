#include "TextEditor.h"
#include "SyntaxHighlighter.h"

#include <QApplication>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QMenu>
#include <QContextMenuEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QCompleter>
#include <QAbstractItemView>
#include <QScrollArea>
#include <QFileInfo>
#include <QAbstractTextDocumentLayout>

TextEditor::TextEditor(QWidget *parent)
    : QTextEdit(parent)
    , m_filePath()
    , m_language("text")
    , m_modified(false)
    , m_lineNumbersVisible(true)
    , m_baseZoomLevel(0)
    , m_lineNumberArea(nullptr)
    , m_syntaxHighlighter(nullptr)
    , m_completer(nullptr)
    , m_cursorTimer(nullptr)
{
    setupEditor();
    setupSyntaxHighlighter();
    
    m_lineNumberArea = new LineNumberArea(this);
    
    connect(document(), &QTextDocument::blockCountChanged, this, &TextEditor::updateLineNumberAreaWidth);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, [this]() { m_lineNumberArea->update(); });
    connect(this, &QTextEdit::cursorPositionChanged, this, &TextEditor::onCursorPositionChanged);
    connect(this, &QTextEdit::textChanged, this, &TextEditor::onTextChanged);
    
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

TextEditor::~TextEditor()
{
}

void TextEditor::setupEditor()
{
    setLineWrapMode(QTextEdit::NoWrap);
    setAcceptRichText(false);
    
    // Set font
    QFont font("Consolas", 10);
    font.setFixedPitch(true);
    setFont(font);
    
    // Set tab width
    QFontMetrics metrics(font);
    setTabStopDistance(4 * metrics.horizontalAdvance(' '));
    
    // Enable drag and drop
    setAcceptDrops(true);
    
    // Setup cursor timer for blink
    m_cursorTimer = new QTimer(this);
    m_cursorTimer->setSingleShot(true);
    connect(m_cursorTimer, &QTimer::timeout, this, &TextEditor::highlightCurrentLine);
}

void TextEditor::setupSyntaxHighlighter()
{
    m_syntaxHighlighter = new SyntaxHighlighter(document());
    m_syntaxHighlighter->setLanguage(m_language);
}

void TextEditor::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
    
    // Auto-detect language from file extension
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);
        QString extension = fileInfo.suffix().toLower();
        
        if (extension == "cpp" || extension == "cxx" || extension == "cc" || extension == "c" || extension == "h" || extension == "hpp") {
            setLanguage("cpp");
        } else if (extension == "py") {
            setLanguage("python");
        } else if (extension == "js" || extension == "ts") {
            setLanguage("javascript");
        } else if (extension == "json") {
            setLanguage("json");
        } else if (extension == "xml" || extension == "html") {
            setLanguage("xml");
        } else {
            setLanguage("text");
        }
    }
}

QString TextEditor::filePath() const
{
    return m_filePath;
}

void TextEditor::setLanguage(const QString &language)
{
    m_language = language;
    if (m_syntaxHighlighter) {
        m_syntaxHighlighter->setLanguage(language);
    }
}

QString TextEditor::language() const
{
    return m_language;
}

bool TextEditor::isModified() const
{
    return m_modified;
}

void TextEditor::setModified(bool modified)
{
    if (m_modified != modified) {
        m_modified = modified;
        emit modificationChanged(modified);
    }
}

void TextEditor::setLineNumbersVisible(bool visible)
{
    m_lineNumbersVisible = visible;
    updateLineNumberAreaWidth(0);
    m_lineNumberArea->setVisible(visible);
}

bool TextEditor::lineNumbersVisible() const
{
    return m_lineNumbersVisible;
}

void TextEditor::setWordWrapMode(QTextOption::WrapMode mode)
{
    if (mode == QTextOption::NoWrap) {
        setLineWrapMode(QTextEdit::NoWrap);
    } else {
        setLineWrapMode(QTextEdit::WidgetWidth);
    }
    QTextOption option = document()->defaultTextOption();
    option.setWrapMode(mode);
    document()->setDefaultTextOption(option);
}

void TextEditor::zoomIn(int range)
{
    m_baseZoomLevel += range;
    QTextEdit::zoomIn(range);
}

void TextEditor::zoomOut(int range)
{
    m_baseZoomLevel -= range;
    QTextEdit::zoomOut(range);
}

void TextEditor::resetZoom()
{
    if (m_baseZoomLevel > 0) {
        QTextEdit::zoomOut(m_baseZoomLevel);
    } else if (m_baseZoomLevel < 0) {
        QTextEdit::zoomIn(-m_baseZoomLevel);
    }
    m_baseZoomLevel = 0;
}

int TextEditor::lineNumberAreaWidth()
{
    if (!m_lineNumbersVisible) {
        return 0;
    }
    
    int digits = 1;
    int max = qMax(1, document()->blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

void TextEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void TextEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        m_lineNumberArea->scroll(0, dy);
    else
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void TextEditor::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void TextEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void TextEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), QColor(240, 240, 240));

    QTextBlock block = document()->firstBlock();
    int blockNumber = 0;
    int top = 0;
    int bottom = 0;

    while (block.isValid()) {
        QRectF blockRect = document()->documentLayout()->blockBoundingRect(block);
        top = (int)blockRect.top();
        bottom = top + (int)blockRect.height();

        if (bottom >= event->rect().top() && top <= event->rect().bottom()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        ++blockNumber;

        if (top > event->rect().bottom())
            break;
    }
}

void TextEditor::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = createStandardContextMenu();
    menu->addSeparator();
    
    QAction *lineNumbersAction = new QAction(tr("Show Line Numbers"), this);
    lineNumbersAction->setCheckable(true);
    lineNumbersAction->setChecked(m_lineNumbersVisible);
    connect(lineNumbersAction, &QAction::triggered, this, [this](bool checked) {
        setLineNumbersVisible(checked);
    });
    menu->addAction(lineNumbersAction);
    
    menu->exec(event->globalPos());
    delete menu;
}

void TextEditor::keyPressEvent(QKeyEvent *event)
{
    if (handleTabIndentation(event)) {
        return;
    }
    
    QTextEdit::keyPressEvent(event);
    
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        autoIndent();
    }
}

void TextEditor::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        const int delta = event->angleDelta().y();
        if (delta > 0) {
            zoomIn();
        } else if (delta < 0) {
            zoomOut();
        }
        event->accept();
        return;
    }
    
    QTextEdit::wheelEvent(event);
}

void TextEditor::onCursorPositionChanged()
{
    highlightCurrentLine();
    
    QTextCursor cursor = textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    emit cursorPositionChanged(line, column);
    
    // Restart cursor timer
    m_cursorTimer->start(500);
}

void TextEditor::onTextChanged()
{
    if (!m_modified) {
        setModified(true);
    }
}

void TextEditor::autoIndent()
{
    QTextCursor cursor = textCursor();
    QTextBlock currentBlock = cursor.block();
    QTextBlock previousBlock = currentBlock.previous();
    
    if (previousBlock.isValid()) {
        QString previousText = previousBlock.text();
        QString indent;
        
        // Extract leading whitespace from previous line
        for (const QChar &ch : previousText) {
            if (ch == ' ' || ch == '\t') {
                indent += ch;
            } else {
                break;
            }
        }
        
        // Add extra indentation for opening braces
        if (previousText.trimmed().endsWith('{') || 
            previousText.trimmed().endsWith(':')) {
            indent += "    "; // Add 4 spaces
        }
        
        cursor.insertText(indent);
    }
}

void TextEditor::matchBrackets()
{
    // TODO: Implement bracket matching
}

bool TextEditor::handleTabIndentation(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        QTextCursor cursor = textCursor();
        if (cursor.hasSelection()) {
            // Indent selected lines
            QTextCursor start = cursor;
            QTextCursor end = cursor;
            start.setPosition(cursor.selectionStart());
            end.setPosition(cursor.selectionEnd());
            
            start.movePosition(QTextCursor::StartOfBlock);
            end.movePosition(QTextCursor::EndOfBlock);
            
            cursor.setPosition(start.position());
            cursor.setPosition(end.position(), QTextCursor::KeepAnchor);
            
            QString selectedText = cursor.selectedText();
            selectedText.replace("\u2029", "\n    "); // Qt uses U+2029 for paragraph separator
            selectedText = "    " + selectedText;
            
            cursor.insertText(selectedText);
            return true;
        } else {
            // Insert tab
            cursor.insertText("    ");
            return true;
        }
    } else if (event->key() == Qt::Key_Backtab) {
        // Unindent
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::StartOfBlock);
        QString blockText = cursor.block().text();
        
        if (blockText.startsWith("    ")) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 4);
            cursor.removeSelectedText();
        } else if (blockText.startsWith("\t")) {
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
            cursor.removeSelectedText();
        }
        return true;
    }
    
    return false;
}

