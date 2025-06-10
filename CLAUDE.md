# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a modern multi-tab text editor built with Qt 6 and C++20. The project demonstrates Qt's text handling capabilities, custom widgets, and modern C++ features in a practical desktop application.

## Development Commands

### Build System
```bash
# Initial setup
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
```

### Dependencies Installation (Ubuntu 24.04)
```bash
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
```

## Architecture Overview

The application follows a hierarchical widget structure:

```
MainWindow
├── MenuBar & ToolBar
├── TabWidget (custom QTabWidget)
│   └── TextEditor[] (custom QTextEdit)
├── StatusBar
├── DockWidgets
│   ├── FileExplorer
│   └── FindReplacePanel
└── SettingsManager
```

### Key Design Patterns
- **Model-View Architecture**: File system integration using QFileSystemModel
- **Signal-Slot Mechanism**: Qt's event handling throughout the application
- **Plugin-like Architecture**: Extensible syntax highlighting system
- **RAII and Smart Pointers**: Modern C++ memory management

## Core Components

### Custom Widget Classes
- **TextEditor**: Custom QTextEdit subclass with enhanced features
- **TabWidget**: Custom QTabWidget for tab management
- **SyntaxHighlighter**: QSyntaxHighlighter subclass for language support
- **FileExplorer**: QTreeView-based file browser
- **FindReplacePanel**: Custom search/replace widget

### Modern C++20 Features Integration
- **Concepts**: Template constraints for file type handlers
- **Ranges**: File processing and text manipulation
- **Coroutines**: Asynchronous file operations (Qt 6.5+)
- **Structured Bindings**: Qt container operations
- **std::format**: String formatting where supported

## File Organization

Expected structure when implemented:
```
src/
├── MainWindow.{h,cpp}      # Main application window
├── TextEditor.{h,cpp}      # Custom text editing widget
├── TabWidget.{h,cpp}       # Tab management
├── SyntaxHighlighter.{h,cpp} # Language syntax support
├── FileExplorer.{h,cpp}    # File browser dock widget
├── FindReplacePanel.{h,cpp} # Search/replace functionality
├── SettingsManager.{h,cpp} # Configuration persistence
└── Utils.{h,cpp}           # Utility functions

resources/
├── icons/                  # Application icons
├── themes/                 # UI themes
└── application.qrc         # Qt resource file
```

## Development Phases

The project is structured in 4 development phases:
1. **Foundation**: Basic MainWindow, TextEditor, and file operations
2. **Core Editing**: Search, status bar, line numbers, recent files
3. **Advanced Text**: Syntax highlighting, auto-indent, bracket matching
4. **UI Polish**: Themes, file explorer, preferences, session management

## Requirements

- Qt 6.4+ (Core, Widgets, GUI modules)
- CMake 3.16+
- C++20 compatible compiler (GCC 10+, Clang 12+)
- Optional: Qt 6.5+ for coroutines support