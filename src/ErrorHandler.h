/**
 * @file ErrorHandler.h
 * @brief Comprehensive error handling and recovery system
 * @author Multi-Tab Editor Team
 * @date 2025
 */

#pragma once

#include <QString>
#include <QMessageBox>
#include <QWidget>
#include <QFileInfo>
#include <QDir>
#include <QStorageInfo>
#include <QApplication>
#include <QProcess>

/**
 * @class ErrorHandler
 * @brief Static utility class for comprehensive error handling and recovery
 * 
 * ErrorHandler provides a centralized system for handling various types of
 * file operations and system errors. It offers:
 * 
 * - Detailed error categorization and user-friendly messages
 * - Recovery suggestions for common error scenarios
 * - File size and memory warnings before operations
 * - System resource monitoring and validation
 * - Large file handling with performance impact warnings
 * - Disk space validation and low space alerts
 * 
 * The class uses Qt's message box system to present errors to users
 * with clear explanations and actionable recovery suggestions.
 * 
 * @see MainWindow, TextEditor
 */
class ErrorHandler
{
public:
    /**
     * @enum ErrorType
     * @brief Categories of errors that can occur during file operations
     */
    enum class ErrorType {
        FileNotFound,     ///< Requested file does not exist
        PermissionDenied, ///< Insufficient permissions for operation
        DiskFull,         ///< Insufficient disk space available
        FileTooLarge,     ///< File exceeds size limits or memory capacity
        FileCorrupted,    ///< File appears to be corrupted or unreadable
        NetworkError,     ///< Network-related error (for remote files)
        MemoryError,      ///< System memory insufficient for operation
        UnknownError      ///< Unclassified or unexpected error
    };

    /**
     * @enum FileOperation
     * @brief Types of file operations that can generate errors
     */
    enum class FileOperation {
        Opening,   ///< Opening/reading a file
        Saving,    ///< Saving/writing a file
        Creating,  ///< Creating a new file
        Deleting,  ///< Deleting an existing file
        Renaming   ///< Renaming/moving a file
    };

    // File operation error handling
    /**
     * @brief Handles file operation errors with detailed messages and recovery options
     * @param parent Parent widget for error dialogs
     * @param filePath Path to the file that caused the error
     * @param errorString System error message from Qt
     * @param operation Type of file operation that failed
     * @param errorType Specific error type (auto-detected if UnknownError)
     * @return true if user chose to retry, false to cancel operation
     * 
     * Displays detailed error information with recovery suggestions and
     * offers retry/cancel options where appropriate.
     */
    static bool handleFileError(QWidget *parent, 
                               const QString &filePath, 
                               const QString &errorString,
                               FileOperation operation,
                               ErrorType errorType = ErrorType::UnknownError);

    // Large file warnings
    /**
     * @brief Warns user about large files before opening
     * @param parent Parent widget for warning dialogs
     * @param filePath Path to the file to check
     * @return true if user wants to proceed, false to cancel
     * 
     * Shows warnings for files >50MB (large) and >200MB (huge)
     * with memory usage estimates and performance impact info.
     */
    static bool checkFileSizeWarning(QWidget *parent, const QString &filePath);
    
    /**
     * @brief Checks system memory availability before operations
     * @param parent Parent widget for warning dialogs
     * @return true if sufficient memory available, false if critically low
     */
    static bool checkMemoryUsage(QWidget *parent);

    // File validation
    /**
     * @brief Validates file path for correctness and security
     * @param parent Parent widget for error dialogs
     * @param filePath Path to validate
     * @return true if path is valid and safe
     */
    static bool validateFilePath(QWidget *parent, const QString &filePath);
    
    /**
     * @brief Checks available disk space before file operations
     * @param parent Parent widget for warning dialogs
     * @param filePath Path where file will be written
     * @param requiredBytes Estimated bytes needed (0 for basic check)
     * @return true if sufficient space available
     */
    static bool checkDiskSpace(QWidget *parent, const QString &filePath, qint64 requiredBytes = 0);
    
    /**
     * @brief Validates file permissions before operations
     * @param parent Parent widget for error dialogs
     * @param filePath Path to check permissions for
     * @param writeAccess true to check write permissions, false for read
     * @return true if required permissions are available
     */
    static bool checkFilePermissions(QWidget *parent, const QString &filePath, bool writeAccess = false);

    // Error message formatting
    /**
     * @brief Creates detailed, user-friendly error messages
     * @param filePath Path to the problematic file
     * @param errorString System error message
     * @param operation File operation that failed
     * @param errorType Category of error
     * @return Formatted error message with context and details
     */
    static QString getDetailedErrorMessage(const QString &filePath, 
                                         const QString &errorString,
                                         FileOperation operation,
                                         ErrorType errorType);

    // Recovery suggestions
    /**
     * @brief Provides actionable recovery suggestions for specific errors
     * @param errorType Category of error that occurred
     * @param operation File operation that failed
     * @return Human-readable recovery suggestions
     */
    static QString getRecoverySuggestion(ErrorType errorType, FileOperation operation);

    // System information for debugging
    /**
     * @brief Gathers system information for debugging purposes
     * @return Formatted string with OS, Qt version, and system specs
     */
    static QString getSystemInfo();
    
    /**
     * @brief Gets available system memory
     * @return Available memory in bytes, or -1 if unable to determine
     */
    static qint64 getAvailableMemory();
    
    /**
     * @brief Gets file size safely
     * @param filePath Path to the file
     * @return File size in bytes, or -1 if file doesn't exist/error
     */
    static qint64 getFileSize(const QString &filePath);

private:
    // Size and memory thresholds
    /** @brief File size threshold for showing large file warning (50MB) */
    static const qint64 LARGE_FILE_THRESHOLD = 50 * 1024 * 1024;
    
    /** @brief File size threshold for showing huge file warning (200MB) */
    static const qint64 HUGE_FILE_THRESHOLD = 200 * 1024 * 1024;
    
    /** @brief Memory threshold for showing low memory warning (100MB) */
    static const qint64 MEMORY_WARNING_THRESHOLD = 100 * 1024 * 1024;
    
    /** @brief Disk space threshold for showing low space warning (100MB) */
    static const qint64 LOW_DISK_SPACE_THRESHOLD = 100 * 1024 * 1024;

    /**
     * @brief Automatically detects error type from system error string
     * @param errorString System error message from Qt
     * @return Best-guess ErrorType based on error message content
     */
    static ErrorType detectErrorType(const QString &errorString);
    
public:
    /**
     * @brief Formats byte count into human-readable file size
     * @param bytes Number of bytes to format
     * @return Formatted string like "1.5 MB", "3.2 GB", etc.
     */
    static QString formatFileSize(qint64 bytes);
};