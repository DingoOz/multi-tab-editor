#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
    , m_currentLanguage("text")
{
    setupPlainTextHighlighting();
}

SyntaxHighlighter::~SyntaxHighlighter()
{
}

void SyntaxHighlighter::setLanguage(const QString &language)
{
    if (m_currentLanguage == language) {
        return;
    }
    
    m_currentLanguage = language;
    m_highlightingRules.clear();
    
    if (language == "cpp" || language == "c") {
        setupCppHighlighting();
    } else if (language == "python") {
        setupPythonHighlighting();
    } else if (language == "javascript") {
        setupJavaScriptHighlighting();
    } else if (language == "json") {
        setupJsonHighlighting();
    } else if (language == "xml" || language == "html") {
        setupXmlHighlighting();
    } else {
        setupPlainTextHighlighting();
    }
    
    rehighlight();
}

QString SyntaxHighlighter::language() const
{
    return m_currentLanguage;
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // Apply highlighting rules
    for (const HighlightingRule &rule : m_highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    
    // Multi-line comment highlighting
    setCurrentBlockState(0);
    
    if (m_currentLanguage == "cpp" || m_currentLanguage == "c" || m_currentLanguage == "javascript") {
        QRegularExpressionMatch startMatch = m_commentStartExpression.match(text);
        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = startMatch.capturedStart();
        
        while (startIndex >= 0) {
            QRegularExpressionMatch endMatch = m_commentEndExpression.match(text, startIndex);
            int endIndex = endMatch.capturedStart();
            int commentLength = 0;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex + endMatch.capturedLength();
            }
            setFormat(startIndex, commentLength, m_multiLineCommentFormat);
            startMatch = m_commentStartExpression.match(text, startIndex + commentLength);
            startIndex = startMatch.capturedStart();
        }
    }
}

void SyntaxHighlighter::setupCppHighlighting()
{
    HighlightingRule rule;
    
    // Keyword format
    m_keywordFormat.setForeground(QColor(86, 156, 214)); // VS Code blue
    m_keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bauto\\b" << "\\bbool\\b" << "\\bbreak\\b" << "\\bcase\\b"
                    << "\\bcatch\\b" << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bconstexpr\\b" << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdelete\\b"
                    << "\\bdo\\b" << "\\bdouble\\b" << "\\belse\\b" << "\\benum\\b"
                    << "\\bexplicit\\b" << "\\bextern\\b" << "\\bfloat\\b" << "\\bfor\\b"
                    << "\\bfriend\\b" << "\\bif\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\bnew\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b" << "\\breturn\\b"
                    << "\\bshort\\b" << "\\bsigned\\b" << "\\bsizeof\\b" << "\\bstatic\\b"
                    << "\\bstruct\\b" << "\\bswitch\\b" << "\\btemplate\\b" << "\\bthis\\b"
                    << "\\bthrow\\b" << "\\btry\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\busing\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b";
    
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_keywordFormat;
        m_highlightingRules.append(rule);
    }
    
    // Class format
    m_classFormat.setForeground(QColor(78, 201, 176)); // VS Code cyan
    m_classFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\b[A-Z][a-zA-Z0-9_]*\\b");
    rule.format = m_classFormat;
    m_highlightingRules.append(rule);
    
    // Single line comment
    m_singleLineCommentFormat.setForeground(QColor(106, 153, 85)); // VS Code green
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);
    
    // Multi-line comment
    m_multiLineCommentFormat.setForeground(QColor(106, 153, 85)); // VS Code green
    m_commentStartExpression = QRegularExpression("/\\*");
    m_commentEndExpression = QRegularExpression("\\*/");
    
    // Quotation
    m_quotationFormat.setForeground(QColor(206, 145, 120)); // VS Code orange
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);
    
    // Function
    m_functionFormat.setForeground(QColor(220, 220, 170)); // VS Code yellow
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = m_functionFormat;
    m_highlightingRules.append(rule);
    
    // Numbers
    m_numberFormat.setForeground(QColor(181, 206, 168)); // VS Code light green
    rule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?\\b");
    rule.format = m_numberFormat;
    m_highlightingRules.append(rule);
    
    // Preprocessor
    m_preprocessorFormat.setForeground(QColor(155, 155, 155)); // VS Code gray
    rule.pattern = QRegularExpression("#[a-zA-Z_][a-zA-Z0-9_]*");
    rule.format = m_preprocessorFormat;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::setupPythonHighlighting()
{
    HighlightingRule rule;
    
    // Keyword format
    m_keywordFormat.setForeground(QColor(86, 156, 214)); // VS Code blue
    m_keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\band\\b" << "\\bas\\b" << "\\bassert\\b" << "\\bbreak\\b"
                    << "\\bclass\\b" << "\\bcontinue\\b" << "\\bdef\\b" << "\\bdel\\b"
                    << "\\belif\\b" << "\\belse\\b" << "\\bexcept\\b" << "\\bexec\\b"
                    << "\\bfinally\\b" << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
                    << "\\bif\\b" << "\\bimport\\b" << "\\bin\\b" << "\\bis\\b"
                    << "\\blambda\\b" << "\\bnot\\b" << "\\bor\\b" << "\\bpass\\b"
                    << "\\bprint\\b" << "\\braise\\b" << "\\breturn\\b" << "\\btry\\b"
                    << "\\bwhile\\b" << "\\bwith\\b" << "\\byield\\b";
    
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_keywordFormat;
        m_highlightingRules.append(rule);
    }
    
    // Class format
    m_classFormat.setForeground(QColor(78, 201, 176)); // VS Code cyan
    m_classFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\b[A-Z][a-zA-Z0-9_]*\\b");
    rule.format = m_classFormat;
    m_highlightingRules.append(rule);
    
    // Single line comment
    m_singleLineCommentFormat.setForeground(QColor(106, 153, 85)); // VS Code green
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);
    
    // Quotation
    m_quotationFormat.setForeground(QColor(206, 145, 120)); // VS Code orange
    rule.pattern = QRegularExpression("\".*\"|'.*'");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);
    
    // Function
    m_functionFormat.setForeground(QColor(220, 220, 170)); // VS Code yellow
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = m_functionFormat;
    m_highlightingRules.append(rule);
    
    // Numbers
    m_numberFormat.setForeground(QColor(181, 206, 168)); // VS Code light green
    rule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?\\b");
    rule.format = m_numberFormat;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::setupJavaScriptHighlighting()
{
    HighlightingRule rule;
    
    // Keyword format
    m_keywordFormat.setForeground(QColor(86, 156, 214)); // VS Code blue
    m_keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b" << "\\bcontinue\\b"
                    << "\\bdefault\\b" << "\\bdelete\\b" << "\\bdo\\b" << "\\belse\\b"
                    << "\\bfinally\\b" << "\\bfor\\b" << "\\bfunction\\b" << "\\bif\\b"
                    << "\\bin\\b" << "\\binstanceof\\b" << "\\bnew\\b" << "\\breturn\\b"
                    << "\\bswitch\\b" << "\\bthis\\b" << "\\bthrow\\b" << "\\btry\\b"
                    << "\\btypeof\\b" << "\\bvar\\b" << "\\bvoid\\b" << "\\bwhile\\b"
                    << "\\bwith\\b" << "\\bconst\\b" << "\\blet\\b";
    
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_keywordFormat;
        m_highlightingRules.append(rule);
    }
    
    // Single line comment
    m_singleLineCommentFormat.setForeground(QColor(106, 153, 85)); // VS Code green
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);
    
    // Multi-line comment
    m_multiLineCommentFormat.setForeground(QColor(106, 153, 85)); // VS Code green
    m_commentStartExpression = QRegularExpression("/\\*");
    m_commentEndExpression = QRegularExpression("\\*/");
    
    // Quotation
    m_quotationFormat.setForeground(QColor(206, 145, 120)); // VS Code orange
    rule.pattern = QRegularExpression("\".*\"|'.*'|`.*`");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);
    
    // Function
    m_functionFormat.setForeground(QColor(220, 220, 170)); // VS Code yellow
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = m_functionFormat;
    m_highlightingRules.append(rule);
    
    // Numbers
    m_numberFormat.setForeground(QColor(181, 206, 168)); // VS Code light green
    rule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?\\b");
    rule.format = m_numberFormat;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::setupJsonHighlighting()
{
    HighlightingRule rule;
    
    // String values
    m_quotationFormat.setForeground(QColor(206, 145, 120)); // VS Code orange
    rule.pattern = QRegularExpression("\"[^\"]*\"");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);
    
    // Numbers
    m_numberFormat.setForeground(QColor(181, 206, 168)); // VS Code light green
    rule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?\\b");
    rule.format = m_numberFormat;
    m_highlightingRules.append(rule);
    
    // Boolean values
    m_keywordFormat.setForeground(QColor(86, 156, 214)); // VS Code blue
    m_keywordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\b(true|false|null)\\b");
    rule.format = m_keywordFormat;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::setupXmlHighlighting()
{
    HighlightingRule rule;
    
    // XML element
    m_classFormat.setForeground(QColor(86, 156, 214)); // VS Code blue
    rule.pattern = QRegularExpression("</?\\b[A-Za-z0-9_-]+(?=\\s|>)");
    rule.format = m_classFormat;
    m_highlightingRules.append(rule);
    
    // XML attribute
    m_functionFormat.setForeground(QColor(220, 220, 170)); // VS Code yellow
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_-]+(?=\\s*=)");
    rule.format = m_functionFormat;
    m_highlightingRules.append(rule);
    
    // XML value
    m_quotationFormat.setForeground(QColor(206, 145, 120)); // VS Code orange
    rule.pattern = QRegularExpression("\"[^\"]*\"|'[^']*'");
    rule.format = m_quotationFormat;
    m_highlightingRules.append(rule);
    
    // XML comment
    m_singleLineCommentFormat.setForeground(QColor(106, 153, 85)); // VS Code green
    rule.pattern = QRegularExpression("<!--[^>]*-->");
    rule.format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);
}

void SyntaxHighlighter::setupPlainTextHighlighting()
{
    // No highlighting for plain text
    m_highlightingRules.clear();
}

