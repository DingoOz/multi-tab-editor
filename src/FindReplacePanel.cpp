#include "FindReplacePanel.h"
#include "TextEditor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QTextCursor>
#include <QTextDocument>

FindReplacePanel::FindReplacePanel(QWidget *parent)
    : QWidget(parent)
    , m_findLineEdit(nullptr)
    , m_replaceLineEdit(nullptr)
    , m_findNextButton(nullptr)
    , m_findPreviousButton(nullptr)
    , m_replaceButton(nullptr)
    , m_replaceAllButton(nullptr)
    , m_closeButton(nullptr)
    , m_caseSensitiveCheckBox(nullptr)
    , m_wholeWordsCheckBox(nullptr)
    , m_useRegexCheckBox(nullptr)
    , m_findLabel(nullptr)
    , m_replaceLabel(nullptr)
    , m_statusLabel(nullptr)
    , m_textEditor(nullptr)
    , m_findPanelVisible(false)
    , m_replacePanelVisible(false)
{
    setupUI();
    setupConnections();
    hidePanels();
}

FindReplacePanel::~FindReplacePanel()
{
}

void FindReplacePanel::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(10, 5, 10, 5);
    
    // Find section
    QHBoxLayout *findLayout = new QHBoxLayout();
    
    m_findLabel = new QLabel(tr("Find:"), this);
    m_findLabel->setMinimumWidth(60);
    
    m_findLineEdit = new QLineEdit(this);
    m_findLineEdit->setPlaceholderText(tr("Enter text to find..."));
    
    m_findNextButton = new QPushButton(tr("Find Next"), this);
    m_findPreviousButton = new QPushButton(tr("Find Previous"), this);
    m_closeButton = new QPushButton(tr("×"), this);
    m_closeButton->setMaximumWidth(25);
    m_closeButton->setToolTip(tr("Close"));
    
    findLayout->addWidget(m_findLabel);
    findLayout->addWidget(m_findLineEdit, 1);
    findLayout->addWidget(m_findPreviousButton);
    findLayout->addWidget(m_findNextButton);
    findLayout->addWidget(m_closeButton);
    
    // Replace section
    QHBoxLayout *replaceLayout = new QHBoxLayout();
    
    m_replaceLabel = new QLabel(tr("Replace:"), this);
    m_replaceLabel->setMinimumWidth(60);
    
    m_replaceLineEdit = new QLineEdit(this);
    m_replaceLineEdit->setPlaceholderText(tr("Enter replacement text..."));
    
    m_replaceButton = new QPushButton(tr("Replace"), this);
    m_replaceAllButton = new QPushButton(tr("Replace All"), this);
    
    replaceLayout->addWidget(m_replaceLabel);
    replaceLayout->addWidget(m_replaceLineEdit, 1);
    replaceLayout->addWidget(m_replaceButton);
    replaceLayout->addWidget(m_replaceAllButton);
    replaceLayout->addStretch();
    
    // Options section
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    
    m_caseSensitiveCheckBox = new QCheckBox(tr("Case sensitive"), this);
    m_wholeWordsCheckBox = new QCheckBox(tr("Whole words"), this);
    m_useRegexCheckBox = new QCheckBox(tr("Regular expression"), this);
    
    m_statusLabel = new QLabel(this);
    m_statusLabel->setStyleSheet("color: gray; font-style: italic;");
    
    optionsLayout->addWidget(m_caseSensitiveCheckBox);
    optionsLayout->addWidget(m_wholeWordsCheckBox);
    optionsLayout->addWidget(m_useRegexCheckBox);
    optionsLayout->addStretch();
    optionsLayout->addWidget(m_statusLabel);
    
    // Add to main layout
    mainLayout->addLayout(findLayout);
    mainLayout->addLayout(replaceLayout);
    mainLayout->addLayout(optionsLayout);
    
    // Initially hide replace section
    m_replaceLabel->hide();
    m_replaceLineEdit->hide();
    m_replaceButton->hide();
    m_replaceAllButton->hide();
}

void FindReplacePanel::setupConnections()
{
    connect(m_findLineEdit, &QLineEdit::textChanged, this, &FindReplacePanel::onFindTextChanged);
    connect(m_findLineEdit, &QLineEdit::returnPressed, this, &FindReplacePanel::findNext);
    connect(m_replaceLineEdit, &QLineEdit::returnPressed, this, &FindReplacePanel::replace);
    
    connect(m_findNextButton, &QPushButton::clicked, this, &FindReplacePanel::findNext);
    connect(m_findPreviousButton, &QPushButton::clicked, this, &FindReplacePanel::findPrevious);
    connect(m_replaceButton, &QPushButton::clicked, this, &FindReplacePanel::replace);
    connect(m_replaceAllButton, &QPushButton::clicked, this, &FindReplacePanel::replaceAll);
    connect(m_closeButton, &QPushButton::clicked, this, &FindReplacePanel::onCloseButtonClicked);
    
    connect(m_caseSensitiveCheckBox, &QCheckBox::toggled, this, &FindReplacePanel::onOptionsChanged);
    connect(m_wholeWordsCheckBox, &QCheckBox::toggled, this, &FindReplacePanel::onOptionsChanged);
    connect(m_useRegexCheckBox, &QCheckBox::toggled, this, &FindReplacePanel::onOptionsChanged);
}

void FindReplacePanel::setTextEditor(TextEditor *editor)
{
    m_textEditor = editor;
    updateFindButtons();
}

TextEditor *FindReplacePanel::textEditor() const
{
    return m_textEditor;
}

void FindReplacePanel::showFindPanel()
{
    m_findPanelVisible = true;
    m_replacePanelVisible = false;
    
    // Show find controls
    m_findLabel->show();
    m_findLineEdit->show();
    m_findNextButton->show();
    m_findPreviousButton->show();
    m_closeButton->show();
    
    // Hide replace controls
    m_replaceLabel->hide();
    m_replaceLineEdit->hide();
    m_replaceButton->hide();
    m_replaceAllButton->hide();
    
    m_findLineEdit->setFocus();
    m_findLineEdit->selectAll();
    
    show();
}

void FindReplacePanel::showReplacePanel()
{
    m_findPanelVisible = true;
    m_replacePanelVisible = true;
    
    // Show all controls
    m_findLabel->show();
    m_findLineEdit->show();
    m_findNextButton->show();
    m_findPreviousButton->show();
    m_closeButton->show();
    
    m_replaceLabel->show();
    m_replaceLineEdit->show();
    m_replaceButton->show();
    m_replaceAllButton->show();
    
    m_findLineEdit->setFocus();
    m_findLineEdit->selectAll();
    
    show();
}

void FindReplacePanel::hidePanels()
{
    m_findPanelVisible = false;
    m_replacePanelVisible = false;
    hide();
}

void FindReplacePanel::setFindText(const QString &text)
{
    m_findLineEdit->setText(text);
}

QString FindReplacePanel::findText() const
{
    return m_findLineEdit->text();
}

void FindReplacePanel::findNext()
{
    if (!m_textEditor || m_findLineEdit->text().isEmpty()) {
        return;
    }
    
    performFind(m_findLineEdit->text(), true);
}

void FindReplacePanel::findPrevious()
{
    if (!m_textEditor || m_findLineEdit->text().isEmpty()) {
        return;
    }
    
    performFind(m_findLineEdit->text(), false);
}

void FindReplacePanel::replace()
{
    if (!m_textEditor || m_findLineEdit->text().isEmpty()) {
        return;
    }
    
    QTextCursor cursor = m_textEditor->textCursor();
    if (cursor.hasSelection()) {
        QString selectedText = cursor.selectedText();
        QString findText = m_findLineEdit->text();
        
        // Check if current selection matches find text
        bool matches = false;
        if (m_caseSensitiveCheckBox->isChecked()) {
            matches = (selectedText == findText);
        } else {
            matches = (selectedText.toLower() == findText.toLower());
        }
        
        if (matches) {
            cursor.insertText(m_replaceLineEdit->text());
        }
    }
    
    // Find next occurrence
    findNext();
}

void FindReplacePanel::replaceAll()
{
    if (!m_textEditor || m_findLineEdit->text().isEmpty()) {
        return;
    }
    
    QTextCursor cursor = m_textEditor->textCursor();
    cursor.movePosition(QTextCursor::Start);
    m_textEditor->setTextCursor(cursor);
    
    int replacements = 0;
    
    while (performFind(m_findLineEdit->text(), true)) {
        QTextCursor currentCursor = m_textEditor->textCursor();
        if (currentCursor.hasSelection()) {
            currentCursor.insertText(m_replaceLineEdit->text());
            replacements++;
        } else {
            break;
        }
    }
    
    m_statusLabel->setText(tr("Replaced %1 occurrence(s)").arg(replacements));
}

void FindReplacePanel::onFindTextChanged()
{
    updateFindButtons();
    
    if (!m_findLineEdit->text().isEmpty()) {
        int matches = countMatches(m_findLineEdit->text());
        if (matches > 0) {
            m_statusLabel->setText(tr("%1 match(es) found").arg(matches));
        } else {
            m_statusLabel->setText(tr("No matches found"));
        }
    } else {
        m_statusLabel->clear();
    }
}

void FindReplacePanel::onOptionsChanged()
{
    onFindTextChanged(); // Refresh match count
}

void FindReplacePanel::onCloseButtonClicked()
{
    hidePanels();
}

void FindReplacePanel::updateFindButtons()
{
    bool hasText = !m_findLineEdit->text().isEmpty();
    bool hasEditor = (m_textEditor != nullptr);
    
    m_findNextButton->setEnabled(hasText && hasEditor);
    m_findPreviousButton->setEnabled(hasText && hasEditor);
    m_replaceButton->setEnabled(hasText && hasEditor && m_replacePanelVisible);
    m_replaceAllButton->setEnabled(hasText && hasEditor && m_replacePanelVisible);
}

bool FindReplacePanel::performFind(const QString &text, bool forward)
{
    if (!m_textEditor || text.isEmpty()) {
        return false;
    }
    
    QTextDocument::FindFlags flags;
    
    if (!forward) {
        flags |= QTextDocument::FindBackward;
    }
    
    if (m_caseSensitiveCheckBox->isChecked()) {
        flags |= QTextDocument::FindCaseSensitively;
    }
    
    if (m_wholeWordsCheckBox->isChecked()) {
        flags |= QTextDocument::FindWholeWords;
    }
    
    QTextCursor cursor;
    
    if (m_useRegexCheckBox->isChecked()) {
        QRegularExpression regex(text);
        if (!m_caseSensitiveCheckBox->isChecked()) {
            regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
        }
        cursor = m_textEditor->document()->find(regex, m_textEditor->textCursor(), flags);
    } else {
        cursor = m_textEditor->document()->find(text, m_textEditor->textCursor(), flags);
    }
    
    if (!cursor.isNull()) {
        m_textEditor->setTextCursor(cursor);
        return true;
    } else {
        // Wrap around search
        QTextCursor startCursor = m_textEditor->textCursor();
        startCursor.movePosition(forward ? QTextCursor::Start : QTextCursor::End);
        
        if (m_useRegexCheckBox->isChecked()) {
            QRegularExpression regex(text);
            if (!m_caseSensitiveCheckBox->isChecked()) {
                regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
            }
            cursor = m_textEditor->document()->find(regex, startCursor, flags);
        } else {
            cursor = m_textEditor->document()->find(text, startCursor, flags);
        }
        
        if (!cursor.isNull()) {
            m_textEditor->setTextCursor(cursor);
            return true;
        }
    }
    
    return false;
}

int FindReplacePanel::countMatches(const QString &text)
{
    if (!m_textEditor || text.isEmpty()) {
        return 0;
    }
    
    QTextDocument::FindFlags flags;
    
    if (m_caseSensitiveCheckBox->isChecked()) {
        flags |= QTextDocument::FindCaseSensitively;
    }
    
    if (m_wholeWordsCheckBox->isChecked()) {
        flags |= QTextDocument::FindWholeWords;
    }
    
    int count = 0;
    QTextCursor cursor = m_textEditor->document()->find(text, 0, flags);
    
    while (!cursor.isNull()) {
        count++;
        cursor = m_textEditor->document()->find(text, cursor, flags);
    }
    
    return count;
}

void FindReplacePanel::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        hidePanels();
        event->accept();
        return;
    }
    
    QWidget::keyPressEvent(event);
}

void FindReplacePanel::closeEvent(QCloseEvent *event)
{
    hidePanels();
    event->accept();
}

