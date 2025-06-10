#include "Utils.h"

#include <QDateTime>
#include <QApplication>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QKeySequence>
#include <QRegularExpression>
#include <QStandardPaths>

namespace Utils
{

QString detectLanguageFromExtension(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();
    
    if (suffix == "cpp" || suffix == "cxx" || suffix == "cc" || suffix == "c" || 
        suffix == "h" || suffix == "hpp" || suffix == "hxx") {
        return "cpp";
    } else if (suffix == "py" || suffix == "pyw") {
        return "python";
    } else if (suffix == "js" || suffix == "jsx" || suffix == "ts" || suffix == "tsx") {
        return "javascript";
    } else if (suffix == "json") {
        return "json";
    } else if (suffix == "xml" || suffix == "html" || suffix == "htm" || suffix == "xhtml") {
        return "xml";
    } else if (suffix == "css" || suffix == "scss" || suffix == "less") {
        return "css";
    } else if (suffix == "md" || suffix == "markdown") {
        return "markdown";
    }
    
    return "text";
}

QString detectLanguageFromContent(const QString &content)
{
    QString trimmedContent = content.trimmed();
    
    // Check for common file patterns
    if (trimmedContent.startsWith("#!/usr/bin/python") || 
        trimmedContent.startsWith("#!/usr/bin/env python")) {
        return "python";
    } else if (trimmedContent.startsWith("#!/bin/bash") || 
               trimmedContent.startsWith("#!/bin/sh")) {
        return "bash";
    } else if (trimmedContent.startsWith("<?xml") || 
               trimmedContent.startsWith("<!DOCTYPE html")) {
        return "xml";
    } else if (trimmedContent.startsWith("{") || trimmedContent.startsWith("[")) {
        // Could be JSON
        return "json";
    }
    
    // Check for common keywords
    if (content.contains(QRegularExpression("\\b(class|def|import)\\s"))) {
        return "python";
    } else if (content.contains(QRegularExpression("\\b(#include|namespace|class)\\s"))) {
        return "cpp";
    } else if (content.contains(QRegularExpression("\\b(function|var|let|const)\\s"))) {
        return "javascript";
    }
    
    return "text";
}

bool isTextFile(const QString &filePath)
{
    QMimeDatabase mimeDb;
    QMimeType mimeType = mimeDb.mimeTypeForFile(filePath);
    
    return mimeType.name().startsWith("text/") || 
           mimeType.inherits("text/plain") ||
           getSupportedTextExtensions().contains(getFileExtension(filePath));
}

QString readFileContent(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    return stream.readAll();
}

bool writeFileContent(const QString &filePath, const QString &content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    stream << content;
    
    return true;
}

QString getFileExtension(const QString &filePath)
{
    return QFileInfo(filePath).suffix().toLower();
}

QString getFileName(const QString &filePath)
{
    return QFileInfo(filePath).fileName();
}

QString getFileBaseName(const QString &filePath)
{
    return QFileInfo(filePath).baseName();
}

QString getFileDirectory(const QString &filePath)
{
    return QFileInfo(filePath).absolutePath();
}

QString formatFileSize(qint64 size)
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;
    
    if (size >= GB) {
        return QString::number(size / GB, 'f', 1) + " GB";
    } else if (size >= MB) {
        return QString::number(size / MB, 'f', 1) + " MB";
    } else if (size >= KB) {
        return QString::number(size / KB, 'f', 1) + " KB";
    } else {
        return QString::number(size) + " bytes";
    }
}

QString formatDateTime(const QDateTime &dateTime)
{
    return dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

QStringList getSupportedTextExtensions()
{
    return QStringList() 
        << "txt" << "cpp" << "c" << "h" << "hpp" << "cxx" << "cc" << "hxx"
        << "py" << "pyw" << "js" << "jsx" << "ts" << "tsx" << "json"
        << "xml" << "html" << "htm" << "xhtml" << "css" << "scss" << "less"
        << "md" << "markdown" << "rst" << "yaml" << "yml" << "ini" << "cfg"
        << "conf" << "log" << "csv" << "tsv" << "sh" << "bash" << "bat"
        << "ps1" << "java" << "kt" << "swift" << "go" << "rs" << "php"
        << "rb" << "pl" << "lua" << "sql" << "r" << "m" << "mm" << "tex";
}

QString getShortcutText(const QKeySequence &keySequence)
{
    return keySequence.toString(QKeySequence::NativeText);
}

QString elideText(const QString &text, int maxLength)
{
    if (text.length() <= maxLength) {
        return text;
    }
    
    return text.left(maxLength - 3) + "...";
}

bool isValidFileName(const QString &fileName)
{
    if (fileName.isEmpty() || fileName == "." || fileName == "..") {
        return false;
    }
    
    // Check for invalid characters
    QRegularExpression invalidChars("[<>:\"/\\\\|?*]");
    if (fileName.contains(invalidChars)) {
        return false;
    }
    
    // Check for reserved names on Windows
    QStringList reservedNames = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
    };
    
    QString baseName = QFileInfo(fileName).baseName().toUpper();
    if (reservedNames.contains(baseName)) {
        return false;
    }
    
    return true;
}

QString sanitizeFileName(const QString &fileName)
{
    QString sanitized = fileName;
    
    // Replace invalid characters with underscores
    QRegularExpression invalidChars("[<>:\"/\\\\|?*]");
    sanitized.replace(invalidChars, "_");
    
    // Remove leading/trailing spaces and dots
    sanitized = sanitized.trimmed();
    while (sanitized.startsWith('.')) {
        sanitized = sanitized.mid(1);
    }
    while (sanitized.endsWith('.')) {
        sanitized.chop(1);
    }
    
    // Ensure it's not empty
    if (sanitized.isEmpty()) {
        sanitized = "untitled";
    }
    
    return sanitized;
}

QString getUniqueFileName(const QString &directory, const QString &baseName, const QString &extension)
{
    QString fileName = baseName;
    if (!extension.isEmpty()) {
        fileName += "." + extension;
    }
    
    QString fullPath = QDir(directory).filePath(fileName);
    
    if (!QFile::exists(fullPath)) {
        return fileName;
    }
    
    int counter = 1;
    while (true) {
        QString numberedName = baseName + QString("_%1").arg(counter);
        if (!extension.isEmpty()) {
            numberedName += "." + extension;
        }
        
        fullPath = QDir(directory).filePath(numberedName);
        if (!QFile::exists(fullPath)) {
            return numberedName;
        }
        
        counter++;
    }
}

bool copyToClipboard(const QString &text)
{
    QClipboard *clipboard = QApplication::clipboard();
    if (clipboard) {
        clipboard->setText(text);
        return true;
    }
    return false;
}

QString getClipboardText()
{
    QClipboard *clipboard = QApplication::clipboard();
    if (clipboard) {
        return clipboard->text();
    }
    return QString();
}

void showInFileManager(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (fileInfo.exists()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
    }
}

QStringList getWordList(const QString &text)
{
    QRegularExpression wordRegex("\\b\\w+\\b");
    QStringList words;
    
    QRegularExpressionMatchIterator i = wordRegex.globalMatch(text);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        words << match.captured(0);
    }
    
    return words;
}

int countLines(const QString &text)
{
    if (text.isEmpty()) {
        return 0;
    }
    
    return text.count('\n') + 1;
}

int countWords(const QString &text)
{
    if (text.isEmpty()) {
        return 0;
    }
    
    QRegularExpression wordRegex("\\b\\w+\\b");
    return text.count(wordRegex);
}

int countCharacters(const QString &text)
{
    return text.length();
}

} // namespace Utils