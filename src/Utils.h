#pragma once

#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QMimeDatabase>
#include <QTextStream>
#include <QStringConverter>
#include <QByteArray>

namespace Utils
{
    QString detectLanguageFromExtension(const QString &filePath);
    
    QString detectLanguageFromContent(const QString &content);
    
    bool isTextFile(const QString &filePath);
    
    QString readFileContent(const QString &filePath);
    
    bool writeFileContent(const QString &filePath, const QString &content);
    
    QString getFileExtension(const QString &filePath);
    
    QString getFileName(const QString &filePath);
    
    QString getFileBaseName(const QString &filePath);
    
    QString getFileDirectory(const QString &filePath);
    
    QString formatFileSize(qint64 size);
    
    QString formatDateTime(const QDateTime &dateTime);
    
    QStringList getSupportedTextExtensions();
    
    QString getShortcutText(const QKeySequence &keySequence);
    
    QString elideText(const QString &text, int maxLength);
    
    bool isValidFileName(const QString &fileName);
    
    QString sanitizeFileName(const QString &fileName);
    
    QString getUniqueFileName(const QString &directory, const QString &baseName, const QString &extension);
    
    bool copyToClipboard(const QString &text);
    
    QString getClipboardText();
    
    void showInFileManager(const QString &filePath);
    
    QStringList getWordList(const QString &text);
    
    int countLines(const QString &text);
    
    int countWords(const QString &text);
    
    int countCharacters(const QString &text);
}