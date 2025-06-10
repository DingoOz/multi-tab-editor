#include "ErrorHandler.h"

#include <QDebug>
#include <QStandardPaths>
#include <QSysInfo>
#include <QThread>
#include <QRegularExpression>
#include <QTextStream>

bool ErrorHandler::handleFileError(QWidget *parent, 
                                  const QString &filePath, 
                                  const QString &errorString,
                                  FileOperation operation,
                                  ErrorType errorType)
{
    if (errorType == ErrorType::UnknownError) {
        errorType = detectErrorType(errorString);
    }

    QString title;
    switch (operation) {
        case FileOperation::Opening:
            title = QObject::tr("Error Opening File");
            break;
        case FileOperation::Saving:
            title = QObject::tr("Error Saving File");
            break;
        case FileOperation::Creating:
            title = QObject::tr("Error Creating File");
            break;
        case FileOperation::Deleting:
            title = QObject::tr("Error Deleting File");
            break;
        case FileOperation::Renaming:
            title = QObject::tr("Error Renaming File");
            break;
    }

    QString message = getDetailedErrorMessage(filePath, errorString, operation, errorType);
    QString suggestion = getRecoverySuggestion(errorType, operation);
    
    if (!suggestion.isEmpty()) {
        message += "\n\n" + QObject::tr("Suggestion: ") + suggestion;
    }

    QMessageBox::StandardButton result = QMessageBox::critical(
        parent, 
        title, 
        message,
        QMessageBox::Retry | QMessageBox::Ignore | QMessageBox::Cancel,
        QMessageBox::Retry
    );

    return result == QMessageBox::Retry;
}

bool ErrorHandler::checkFileSizeWarning(QWidget *parent, const QString &filePath)
{
    qint64 fileSize = getFileSize(filePath);
    
    if (fileSize < 0) {
        return true; // File doesn't exist or error getting size, proceed anyway
    }

    if (fileSize > HUGE_FILE_THRESHOLD) {
        QMessageBox::StandardButton result = QMessageBox::warning(
            parent,
            QObject::tr("Very Large File"),
            QObject::tr("The file '%1' is very large (%2).\n\n"
                       "Opening this file may:\n"
                       "• Take a long time\n"
                       "• Use significant memory\n"
                       "• Make the editor unresponsive\n\n"
                       "Do you want to continue?")
                .arg(QFileInfo(filePath).fileName())
                .arg(formatFileSize(fileSize)),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );
        return result == QMessageBox::Yes;
    }
    
    if (fileSize > LARGE_FILE_THRESHOLD) {
        QMessageBox::StandardButton result = QMessageBox::information(
            parent,
            QObject::tr("Large File"),
            QObject::tr("The file '%1' is large (%2).\n\n"
                       "This may take a moment to load and use more memory.")
                .arg(QFileInfo(filePath).fileName())
                .arg(formatFileSize(fileSize)),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok
        );
        return result == QMessageBox::Ok;
    }

    return true;
}

bool ErrorHandler::checkMemoryUsage(QWidget *parent)
{
    qint64 availableMemory = getAvailableMemory();
    
    if (availableMemory > 0 && availableMemory < MEMORY_WARNING_THRESHOLD) {
        QMessageBox::StandardButton result = QMessageBox::warning(
            parent,
            QObject::tr("Low Memory"),
            QObject::tr("System memory is running low (%1 available).\n\n"
                       "Consider closing some applications or files before continuing.")
                .arg(formatFileSize(availableMemory)),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Cancel
        );
        return result == QMessageBox::Ok;
    }

    return true;
}

bool ErrorHandler::validateFilePath(QWidget *parent, const QString &filePath)
{
    if (filePath.isEmpty()) {
        QMessageBox::warning(parent, QObject::tr("Invalid File Path"), 
                           QObject::tr("The file path is empty."));
        return false;
    }

    QFileInfo fileInfo(filePath);
    QString dirPath = fileInfo.absolutePath();
    
    // Check if directory exists
    if (!QDir(dirPath).exists()) {
        QMessageBox::StandardButton result = QMessageBox::question(
            parent,
            QObject::tr("Directory Does Not Exist"),
            QObject::tr("The directory '%1' does not exist.\n\nDo you want to create it?")
                .arg(dirPath),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes
        );
        
        if (result == QMessageBox::Yes) {
            QDir().mkpath(dirPath);
            return QDir(dirPath).exists();
        }
        return false;
    }

    // Check directory permissions
    QFileInfo dirInfo(dirPath);
    if (!dirInfo.isWritable()) {
        QMessageBox::critical(parent, QObject::tr("Permission Denied"),
                            QObject::tr("You don't have permission to write to the directory '%1'.")
                                .arg(dirPath));
        return false;
    }

    return true;
}

bool ErrorHandler::checkDiskSpace(QWidget *parent, const QString &filePath, qint64 requiredBytes)
{
    QStorageInfo storage(filePath);
    qint64 availableBytes = storage.bytesAvailable();
    
    if (availableBytes < LOW_DISK_SPACE_THRESHOLD) {
        QMessageBox::warning(
            parent,
            QObject::tr("Low Disk Space"),
            QObject::tr("Disk space is running low (%1 available on %2).\n\n"
                       "You may not be able to save files.")
                .arg(formatFileSize(availableBytes))
                .arg(storage.rootPath())
        );
        return false;
    }
    
    if (requiredBytes > 0 && availableBytes < requiredBytes) {
        QMessageBox::critical(
            parent,
            QObject::tr("Insufficient Disk Space"),
            QObject::tr("Not enough disk space to complete this operation.\n\n"
                       "Required: %1\nAvailable: %2")
                .arg(formatFileSize(requiredBytes))
                .arg(formatFileSize(availableBytes))
        );
        return false;
    }

    return true;
}

bool ErrorHandler::checkFilePermissions(QWidget *parent, const QString &filePath, bool writeAccess)
{
    QFileInfo fileInfo(filePath);
    
    if (!fileInfo.exists()) {
        return true; // File doesn't exist, check will be done during creation
    }

    if (!fileInfo.isReadable()) {
        QMessageBox::critical(parent, QObject::tr("Permission Denied"),
                            QObject::tr("You don't have permission to read the file '%1'.")
                                .arg(fileInfo.fileName()));
        return false;
    }

    if (writeAccess && !fileInfo.isWritable()) {
        QMessageBox::StandardButton result = QMessageBox::warning(
            parent,
            QObject::tr("Read-Only File"),
            QObject::tr("The file '%1' is read-only.\n\n"
                       "Do you want to try to make it writable?")
                .arg(fileInfo.fileName()),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );
        
        if (result == QMessageBox::Yes) {
            QFile file(filePath);
            bool success = file.setPermissions(file.permissions() | QFileDevice::WriteUser);
            if (!success) {
                QMessageBox::critical(parent, QObject::tr("Permission Error"),
                                    QObject::tr("Could not make the file writable."));
            }
            return success;
        }
        return false;
    }

    return true;
}

QString ErrorHandler::getDetailedErrorMessage(const QString &filePath, 
                                            const QString &errorString,
                                            FileOperation operation,
                                            ErrorType errorType)
{
    QFileInfo fileInfo(filePath);
    QString operationText;
    
    switch (operation) {
        case FileOperation::Opening:
            operationText = QObject::tr("open");
            break;
        case FileOperation::Saving:
            operationText = QObject::tr("save");
            break;
        case FileOperation::Creating:
            operationText = QObject::tr("create");
            break;
        case FileOperation::Deleting:
            operationText = QObject::tr("delete");
            break;
        case FileOperation::Renaming:
            operationText = QObject::tr("rename");
            break;
    }

    QString message = QObject::tr("Failed to %1 the file '%2'.")
                        .arg(operationText)
                        .arg(fileInfo.fileName());

    // Add specific error details based on error type
    switch (errorType) {
        case ErrorType::FileNotFound:
            message += "\n\n" + QObject::tr("The file was not found. It may have been moved, renamed, or deleted.");
            break;
        case ErrorType::PermissionDenied:
            message += "\n\n" + QObject::tr("Access denied. You don't have the necessary permissions.");
            break;
        case ErrorType::DiskFull:
            message += "\n\n" + QObject::tr("The disk is full. Free up some space and try again.");
            break;
        case ErrorType::FileTooLarge:
            message += "\n\n" + QObject::tr("The file is too large for this operation.");
            break;
        case ErrorType::FileCorrupted:
            message += "\n\n" + QObject::tr("The file appears to be corrupted or in an unsupported format.");
            break;
        case ErrorType::NetworkError:
            message += "\n\n" + QObject::tr("Network error occurred while accessing the file.");
            break;
        case ErrorType::MemoryError:
            message += "\n\n" + QObject::tr("Not enough memory available for this operation.");
            break;
        case ErrorType::UnknownError:
        default:
            if (!errorString.isEmpty()) {
                message += "\n\n" + QObject::tr("System error: %1").arg(errorString);
            }
            break;
    }

    // Add file path for debugging
    message += "\n\n" + QObject::tr("File path: %1").arg(QDir::toNativeSeparators(filePath));

    return message;
}

QString ErrorHandler::getRecoverySuggestion(ErrorType errorType, FileOperation operation)
{
    switch (errorType) {
        case ErrorType::FileNotFound:
            if (operation == FileOperation::Opening) {
                return QObject::tr("Check the file path and ensure the file exists.");
            }
            break;
        case ErrorType::PermissionDenied:
            return QObject::tr("Check file permissions or try running as administrator.");
        case ErrorType::DiskFull:
            return QObject::tr("Free up disk space by deleting unnecessary files.");
        case ErrorType::FileTooLarge:
            return QObject::tr("Try opening the file with a different application designed for large files.");
        case ErrorType::FileCorrupted:
            return QObject::tr("Try opening a backup copy of the file if available.");
        case ErrorType::NetworkError:
            return QObject::tr("Check your network connection and try again.");
        case ErrorType::MemoryError:
            return QObject::tr("Close other applications to free up memory.");
        default:
            return QString();
    }
    return QString();
}

QString ErrorHandler::getSystemInfo()
{
    QString info;
    info += QObject::tr("System: %1 %2\n").arg(QSysInfo::productType(), QSysInfo::productVersion());
    info += QObject::tr("Qt Version: %1\n").arg(QT_VERSION_STR);
    info += QObject::tr("Available Memory: %1\n").arg(formatFileSize(getAvailableMemory()));
    
    return info;
}

qint64 ErrorHandler::getAvailableMemory()
{
    // This is a simplified estimation - in a real application you might want
    // to use platform-specific APIs for more accurate memory information
#ifdef Q_OS_LINUX
    QFile file("/proc/meminfo");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString line;
        while (stream.readLineInto(&line)) {
            if (line.startsWith("MemAvailable:")) {
                QStringList parts = line.split(QRegularExpression("\\s+"));
                if (parts.size() >= 2) {
                    return parts[1].toLongLong() * 1024; // Convert KB to bytes
                }
            }
        }
    }
#endif
    return -1; // Unknown
}

qint64 ErrorHandler::getFileSize(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if (fileInfo.exists() && fileInfo.isFile()) {
        return fileInfo.size();
    }
    return -1;
}

ErrorHandler::ErrorType ErrorHandler::detectErrorType(const QString &errorString)
{
    QString error = errorString.toLower();
    
    if (error.contains("permission") || error.contains("access denied")) {
        return ErrorType::PermissionDenied;
    }
    if (error.contains("not found") || error.contains("no such file")) {
        return ErrorType::FileNotFound;
    }
    if (error.contains("disk full") || error.contains("no space")) {
        return ErrorType::DiskFull;
    }
    if (error.contains("too large") || error.contains("file size")) {
        return ErrorType::FileTooLarge;
    }
    if (error.contains("corrupt") || error.contains("invalid format")) {
        return ErrorType::FileCorrupted;
    }
    if (error.contains("network") || error.contains("connection")) {
        return ErrorType::NetworkError;
    }
    if (error.contains("memory") || error.contains("out of memory")) {
        return ErrorType::MemoryError;
    }
    
    return ErrorType::UnknownError;
}

QString ErrorHandler::formatFileSize(qint64 bytes)
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;
    
    if (bytes >= GB) {
        return QObject::tr("%1 GB").arg(QString::number(bytes / (double)GB, 'f', 1));
    } else if (bytes >= MB) {
        return QObject::tr("%1 MB").arg(QString::number(bytes / (double)MB, 'f', 1));
    } else if (bytes >= KB) {
        return QObject::tr("%1 KB").arg(QString::number(bytes / (double)KB, 'f', 1));
    } else {
        return QObject::tr("%1 bytes").arg(bytes);
    }
}