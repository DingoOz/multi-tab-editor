/**
 * @file Utils.h
 * @brief Utility functions for file operations, text processing, and system integration
 * @author Multi-Tab Editor Team
 * @date 2025
 */

#pragma once

#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QMimeDatabase>
#include <QTextStream>
#include <QStringConverter>
#include <QByteArray>

/**
 * @namespace Utils
 * @brief Collection of utility functions for the Multi-Tab Text Editor
 * 
 * The Utils namespace provides various helper functions for:
 * - File type detection and language identification
 * - File I/O operations with encoding detection
 * - Text processing and analysis
 * - System integration (clipboard, file manager)
 * - File name validation and sanitization
 * - Date/time and size formatting
 * 
 * These utilities are used throughout the application to provide
 * consistent file handling and text processing capabilities.
 */
namespace Utils
{
    // Language Detection
    /**
     * @brief Detects programming language from file extension
     * @param filePath Full path to the file
     * @return Language identifier (cpp, python, javascript, etc.) or "plain" if unknown
     */
    QString detectLanguageFromExtension(const QString &filePath);
    
    /**
     * @brief Attempts to detect language from file content analysis
     * @param content Text content to analyze
     * @return Best guess language identifier based on content patterns
     */
    QString detectLanguageFromContent(const QString &content);
    
    // File Type Detection
    /**
     * @brief Checks if file is a text file (not binary)
     * @param filePath Full path to the file to check
     * @return true if file appears to be text-based
     */
    bool isTextFile(const QString &filePath);
    
    // File I/O Operations
    /**
     * @brief Reads complete file content with encoding detection
     * @param filePath Full path to the file to read
     * @return File content as QString, or empty string on error
     */
    QString readFileContent(const QString &filePath);
    
    /**
     * @brief Writes content to file with UTF-8 encoding
     * @param filePath Full path to the file to write
     * @param content Text content to write
     * @return true if write was successful
     */
    bool writeFileContent(const QString &filePath, const QString &content);
    
    // File Path Utilities
    /**
     * @brief Extracts file extension from path
     * @param filePath Full path to the file
     * @return File extension (without dot) or empty string if none
     */
    QString getFileExtension(const QString &filePath);
    
    /**
     * @brief Extracts filename with extension from path
     * @param filePath Full path to the file
     * @return Filename portion of the path
     */
    QString getFileName(const QString &filePath);
    
    /**
     * @brief Extracts filename without extension from path
     * @param filePath Full path to the file
     * @return Base filename without extension
     */
    QString getFileBaseName(const QString &filePath);
    
    /**
     * @brief Extracts directory path from file path
     * @param filePath Full path to the file
     * @return Directory portion of the path
     */
    QString getFileDirectory(const QString &filePath);
    
    // Formatting Utilities
    /**
     * @brief Formats byte count into human-readable size string
     * @param size Size in bytes
     * @return Formatted string like "1.5 MB", "3.2 GB", etc.
     */
    QString formatFileSize(qint64 size);
    
    /**
     * @brief Formats QDateTime into user-friendly string
     * @param dateTime Date/time to format
     * @return Formatted date/time string
     */
    QString formatDateTime(const QDateTime &dateTime);
    
    // Application Support
    /**
     * @brief Gets list of file extensions supported by the editor
     * @return List of file extensions (without dots) that can be opened
     */
    QStringList getSupportedTextExtensions();
    
    /**
     * @brief Converts QKeySequence to display string
     * @param keySequence Key sequence to format
     * @return Human-readable shortcut string (e.g., "Ctrl+S")
     */
    QString getShortcutText(const QKeySequence &keySequence);
    
    // Text Processing
    /**
     * @brief Truncates text to maximum length with ellipsis
     * @param text Text to truncate
     * @param maxLength Maximum length before truncation
     * @return Truncated text with "..." if longer than maxLength
     */
    QString elideText(const QString &text, int maxLength);
    
    // File Name Validation
    /**
     * @brief Checks if filename contains only valid characters
     * @param fileName Filename to validate
     * @return true if filename is valid for the current OS
     */
    bool isValidFileName(const QString &fileName);
    
    /**
     * @brief Removes or replaces invalid characters in filename
     * @param fileName Filename to sanitize
     * @return Sanitized filename safe for the current OS
     */
    QString sanitizeFileName(const QString &fileName);
    
    /**
     * @brief Generates unique filename in directory
     * @param directory Target directory path
     * @param baseName Base filename without extension
     * @param extension File extension (with or without dot)
     * @return Unique filename that doesn't exist in directory
     */
    QString getUniqueFileName(const QString &directory, const QString &baseName, const QString &extension);
    
    // System Integration
    /**
     * @brief Copies text to system clipboard
     * @param text Text to copy to clipboard
     * @return true if copy was successful
     */
    bool copyToClipboard(const QString &text);
    
    /**
     * @brief Gets text from system clipboard
     * @return Clipboard text content or empty string if none
     */
    QString getClipboardText();
    
    /**
     * @brief Opens file location in system file manager
     * @param filePath Full path to file to show
     * 
     * Opens the file's parent directory and selects the file
     * in the default file manager (Explorer, Finder, Nautilus).
     */
    void showInFileManager(const QString &filePath);
    
    // Text Analysis
    /**
     * @brief Extracts list of words from text
     * @param text Text to analyze
     * @return List of words (whitespace and punctuation separated)
     */
    QStringList getWordList(const QString &text);
    
    /**
     * @brief Counts number of lines in text
     * @param text Text to analyze
     * @return Number of lines (line breaks + 1)
     */
    int countLines(const QString &text);
    
    /**
     * @brief Counts number of words in text
     * @param text Text to analyze
     * @return Number of words (whitespace separated)
     */
    int countWords(const QString &text);
    
    /**
     * @brief Counts number of characters in text
     * @param text Text to analyze
     * @return Total character count including whitespace
     */
    int countCharacters(const QString &text);
}