#pragma once

#include <QString>
#include <QMessageBox>
#include <QWidget>
#include <QFileInfo>
#include <QDir>
#include <QStorageInfo>
#include <QApplication>
#include <QProcess>

class ErrorHandler
{
public:
    enum class ErrorType {
        FileNotFound,
        PermissionDenied,
        DiskFull,
        FileTooLarge,
        FileCorrupted,
        NetworkError,
        MemoryError,
        UnknownError
    };

    enum class FileOperation {
        Opening,
        Saving,
        Creating,
        Deleting,
        Renaming
    };

    // File operation error handling
    static bool handleFileError(QWidget *parent, 
                               const QString &filePath, 
                               const QString &errorString,
                               FileOperation operation,
                               ErrorType errorType = ErrorType::UnknownError);

    // Large file warnings
    static bool checkFileSizeWarning(QWidget *parent, const QString &filePath);
    static bool checkMemoryUsage(QWidget *parent);

    // File validation
    static bool validateFilePath(QWidget *parent, const QString &filePath);
    static bool checkDiskSpace(QWidget *parent, const QString &filePath, qint64 requiredBytes = 0);
    static bool checkFilePermissions(QWidget *parent, const QString &filePath, bool writeAccess = false);

    // Error message formatting
    static QString getDetailedErrorMessage(const QString &filePath, 
                                         const QString &errorString,
                                         FileOperation operation,
                                         ErrorType errorType);

    // Recovery suggestions
    static QString getRecoverySuggestion(ErrorType errorType, FileOperation operation);

    // System information for debugging
    static QString getSystemInfo();
    static qint64 getAvailableMemory();
    static qint64 getFileSize(const QString &filePath);

private:
    static const qint64 LARGE_FILE_THRESHOLD = 50 * 1024 * 1024; // 50MB
    static const qint64 HUGE_FILE_THRESHOLD = 200 * 1024 * 1024; // 200MB
    static const qint64 MEMORY_WARNING_THRESHOLD = 100 * 1024 * 1024; // 100MB
    static const qint64 LOW_DISK_SPACE_THRESHOLD = 100 * 1024 * 1024; // 100MB

    static ErrorType detectErrorType(const QString &errorString);
public:
    static QString formatFileSize(qint64 bytes);
};