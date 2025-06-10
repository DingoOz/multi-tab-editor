#pragma once

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QHash>
#include <QTextBlockUserData>

struct HighlightingRule
{
    QRegularExpression pattern;
    QTextCharFormat format;
};

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);
    ~SyntaxHighlighter();

    void setLanguage(const QString &language);
    QString language() const;

protected:
    void highlightBlock(const QString &text) override;

private:
    void setupCppHighlighting();
    void setupPythonHighlighting();
    void setupJavaScriptHighlighting();
    void setupJsonHighlighting();
    void setupXmlHighlighting();
    void setupPlainTextHighlighting();
    
    QVector<HighlightingRule> m_highlightingRules;
    
    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_classFormat;
    QTextCharFormat m_singleLineCommentFormat;
    QTextCharFormat m_multiLineCommentFormat;
    QTextCharFormat m_quotationFormat;
    QTextCharFormat m_functionFormat;
    QTextCharFormat m_numberFormat;
    QTextCharFormat m_operatorFormat;
    QTextCharFormat m_preprocessorFormat;
    
    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;
    
    QString m_currentLanguage;
};