/**
 * @file SyntaxHighlighter.h
 * @brief Syntax highlighting system for multiple programming languages
 * @author Multi-Tab Editor Team
 * @date 2025
 */

#pragma once

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QHash>
#include <QTextBlockUserData>

/**
 * @struct HighlightingRule
 * @brief Associates a regular expression pattern with text formatting
 * 
 * Used by SyntaxHighlighter to define highlighting rules for different
 * language elements like keywords, strings, comments, etc.
 */
struct HighlightingRule
{
    QRegularExpression pattern; ///< Regular expression to match text
    QTextCharFormat format;     ///< Formatting to apply to matched text
};

/**
 * @class SyntaxHighlighter
 * @brief Multi-language syntax highlighter for the text editor
 * 
 * SyntaxHighlighter extends QSyntaxHighlighter to provide syntax highlighting
 * for multiple programming languages:
 * - C/C++ with keywords, preprocessor directives, and comments
 * - Python with indentation-aware highlighting
 * - JavaScript with modern ES6+ features
 * - JSON with proper structure highlighting
 * - XML with tag and attribute highlighting
 * - Plain text (no highlighting)
 * 
 * The highlighter automatically detects language based on file extension
 * and applies appropriate color schemes for different syntax elements.
 * 
 * @see TextEditor, HighlightingRule
 */
class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    /**
     * @brief Constructs syntax highlighter for given document
     * @param parent Text document to apply highlighting to
     */
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);
    
    /**
     * @brief Destructor - cleans up highlighting resources
     */
    ~SyntaxHighlighter();

    /**
     * @brief Sets the programming language for highlighting
     * @param language Language identifier (cpp, python, javascript, json, xml, plain)
     * 
     * Changes the highlighting rules to match the specified language.
     * Triggers re-highlighting of the entire document.
     */
    void setLanguage(const QString &language);
    
    /**
     * @brief Gets the current programming language
     * @return Language identifier currently in use
     */
    QString language() const;

protected:
    /**
     * @brief Highlights a single text block (required by QSyntaxHighlighter)
     * @param text Text content of the block to highlight
     * 
     * Applies all highlighting rules to the text block and handles
     * multi-line constructs like block comments.
     */
    void highlightBlock(const QString &text) override;

private:
    // Language Setup Methods
    /** @brief Configures highlighting rules for C/C++ syntax */
    void setupCppHighlighting();
    
    /** @brief Configures highlighting rules for Python syntax */
    void setupPythonHighlighting();
    
    /** @brief Configures highlighting rules for JavaScript syntax */
    void setupJavaScriptHighlighting();
    
    /** @brief Configures highlighting rules for JSON syntax */
    void setupJsonHighlighting();
    
    /** @brief Configures highlighting rules for XML/HTML syntax */
    void setupXmlHighlighting();
    
    /** @brief Disables syntax highlighting for plain text */
    void setupPlainTextHighlighting();
    
    // Highlighting Data
    /** @brief Vector of all highlighting rules for current language */
    QVector<HighlightingRule> m_highlightingRules;
    
    // Text Formats for Different Elements
    /** @brief Format for language keywords (if, while, class, etc.) */
    QTextCharFormat m_keywordFormat;
    
    /** @brief Format for class and type names */
    QTextCharFormat m_classFormat;
    
    /** @brief Format for single-line comments (// in C++, # in Python) */
    QTextCharFormat m_singleLineCommentFormat;
    
    /** @brief Format for multi-line comments (block comments) */
    QTextCharFormat m_multiLineCommentFormat;
    
    /** @brief Format for quoted strings and character literals */
    QTextCharFormat m_quotationFormat;
    
    /** @brief Format for function names and calls */
    QTextCharFormat m_functionFormat;
    
    /** @brief Format for numeric literals */
    QTextCharFormat m_numberFormat;
    
    /** @brief Format for operators (+, -, *, etc.) */
    QTextCharFormat m_operatorFormat;
    
    /** @brief Format for preprocessor directives (#include, #define) */
    QTextCharFormat m_preprocessorFormat;
    
    // Multi-line Comment Handling
    /** @brief Regular expression to find start of block comments */
    QRegularExpression m_commentStartExpression;
    
    /** @brief Regular expression to find end of block comments */
    QRegularExpression m_commentEndExpression;
    
    /** @brief Currently active language identifier */
    QString m_currentLanguage;
};