/**
 * @file ThemeManager.h
 * @brief Theme management system for the Multi-Tab Text Editor
 * @author Multi-Tab Editor Team
 * @date 2025
 */

#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>

class SettingsManager;

/**
 * @class ThemeManager
 * @brief Manages application themes and provides theme switching functionality
 * 
 * ThemeManager handles loading, applying, and switching between different UI themes.
 * It supports both built-in themes (light, dark) and custom user themes.
 * 
 * Features:
 * - Automatic theme detection and loading
 * - Theme switching with immediate application
 * - Theme validation and error handling
 * - Integration with SettingsManager for persistence
 * 
 * @see SettingsManager, MainWindow
 */
class ThemeManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Theme identifiers for built-in themes
     */
    enum class Theme {
        Light,      ///< Light theme with bright backgrounds
        Dark,       ///< Dark theme with dark backgrounds
        Auto,       ///< Automatic theme based on system preferences
        Custom      ///< User-defined custom theme
    };

    /**
     * @brief Constructs theme manager
     * @param settingsManager Settings manager for theme persistence
     * @param parent Parent QObject
     */
    explicit ThemeManager(SettingsManager *settingsManager, QObject *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~ThemeManager();

    /**
     * @brief Gets list of available theme names
     * @return List of theme identifiers (e.g., "light", "dark")
     */
    QStringList getAvailableThemes() const;
    
    /**
     * @brief Gets currently active theme name
     * @return Current theme identifier
     */
    QString getCurrentTheme() const;
    
    /**
     * @brief Applies a theme by name
     * @param themeName Theme identifier to apply
     * @return true if theme was successfully applied
     */
    bool applyTheme(const QString &themeName);
    
    /**
     * @brief Applies a theme by enum value
     * @param theme Theme enum value to apply
     * @return true if theme was successfully applied
     */
    bool applyTheme(Theme theme);
    
    /**
     * @brief Loads and applies theme from settings
     * @return true if theme was successfully loaded and applied
     */
    bool loadSavedTheme();
    
    /**
     * @brief Checks if a theme exists and is valid
     * @param themeName Theme identifier to check
     * @return true if theme exists and can be loaded
     */
    bool isThemeAvailable(const QString &themeName) const;
    
    /**
     * @brief Gets the display name for a theme
     * @param themeName Theme identifier
     * @return Human-readable theme name
     */
    QString getThemeDisplayName(const QString &themeName) const;
    
    /**
     * @brief Converts theme enum to string identifier
     * @param theme Theme enum value
     * @return String identifier for the theme
     */
    static QString themeToString(Theme theme);
    
    /**
     * @brief Converts string identifier to theme enum
     * @param themeName String identifier
     * @return Theme enum value, or Theme::Light if invalid
     */
    static Theme stringToTheme(const QString &themeName);
    
    /**
     * @brief Detects system theme preference (light/dark)
     * @return Theme::Light or Theme::Dark based on system settings
     */
    static Theme detectSystemTheme();

public slots:
    /**
     * @brief Switches to light theme
     */
    void setLightTheme();
    
    /**
     * @brief Switches to dark theme
     */
    void setDarkTheme();
    
    /**
     * @brief Switches to automatic theme (follows system)
     */
    void setAutoTheme();
    
    /**
     * @brief Reloads current theme (useful after theme file changes)
     */
    void reloadCurrentTheme();

signals:
    /**
     * @brief Emitted when theme is successfully changed
     * @param themeName New theme identifier
     */
    void themeChanged(const QString &themeName);
    
    /**
     * @brief Emitted when theme application fails
     * @param themeName Theme that failed to load
     * @param error Error message
     */
    void themeError(const QString &themeName, const QString &error);

private slots:
    /**
     * @brief Handles system theme changes (if supported)
     */
    void onSystemThemeChanged();

private:
    /**
     * @brief Discovers available themes in the themes directory
     */
    void discoverThemes();
    
    /**
     * @brief Loads theme stylesheet from file
     * @param themeName Theme identifier
     * @return Stylesheet content or empty string if failed
     */
    QString loadThemeStylesheet(const QString &themeName) const;
    
    /**
     * @brief Gets the file path for a theme
     * @param themeName Theme identifier
     * @return Full path to theme file
     */
    QString getThemeFilePath(const QString &themeName) const;
    
    /**
     * @brief Applies stylesheet to application
     * @param stylesheet QSS stylesheet content
     */
    void applyStylesheet(const QString &stylesheet);
    
    /**
     * @brief Validates theme stylesheet content
     * @param stylesheet Stylesheet to validate
     * @return true if stylesheet appears valid
     */
    bool validateStylesheet(const QString &stylesheet) const;
    
    /**
     * @brief Sets up system theme monitoring (if supported)
     */
    void setupSystemThemeMonitoring();

    /** @brief Settings manager for theme persistence */
    SettingsManager *m_settingsManager;
    
    /** @brief Currently active theme identifier */
    QString m_currentTheme;
    
    /** @brief Path to themes directory */
    QString m_themesPath;
    
    /** @brief List of available theme names */
    QStringList m_availableThemes;
    
    /** @brief Whether auto theme is enabled */
    bool m_autoThemeEnabled;
    
    // Default theme identifiers
    static const QString LIGHT_THEME;
    static const QString DARK_THEME;
    static const QString AUTO_THEME;
    static const QString DEFAULT_THEME;
};