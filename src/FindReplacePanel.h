#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QTextEdit>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QRegularExpression>

class TextEditor;

class FindReplacePanel : public QWidget
{
    Q_OBJECT

public:
    explicit FindReplacePanel(QWidget *parent = nullptr);
    ~FindReplacePanel();

    void setTextEditor(TextEditor *editor);
    TextEditor *textEditor() const;
    
    void showFindPanel();
    void showReplacePanel();
    void hidePanels();
    
    void setFindText(const QString &text);
    QString findText() const;

public slots:
    void findNext();
    void findPrevious();
    void replace();
    void replaceAll();
    void onFindTextChanged();

signals:
    void findRequested(const QString &text, bool caseSensitive, bool wholeWords, bool useRegex);
    void replaceRequested(const QString &findText, const QString &replaceText, bool caseSensitive, bool wholeWords, bool useRegex);
    void replaceAllRequested(const QString &findText, const QString &replaceText, bool caseSensitive, bool wholeWords, bool useRegex);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onOptionsChanged();
    void onCloseButtonClicked();

private:
    void setupUI();
    void setupConnections();
    void updateFindButtons();
    bool performFind(const QString &text, bool forward = true);
    int countMatches(const QString &text);
    
    QLineEdit *m_findLineEdit;
    QLineEdit *m_replaceLineEdit;
    QPushButton *m_findNextButton;
    QPushButton *m_findPreviousButton;
    QPushButton *m_replaceButton;
    QPushButton *m_replaceAllButton;
    QPushButton *m_closeButton;
    
    QCheckBox *m_caseSensitiveCheckBox;
    QCheckBox *m_wholeWordsCheckBox;
    QCheckBox *m_useRegexCheckBox;
    
    QLabel *m_findLabel;
    QLabel *m_replaceLabel;
    QLabel *m_statusLabel;
    
    TextEditor *m_textEditor;
    bool m_findPanelVisible;
    bool m_replacePanelVisible;
};