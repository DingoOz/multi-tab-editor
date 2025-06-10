# Multi-tab Text Editor - Development Plan

## Project Overview

A modern multi-tab text editor built with Qt 6 and C++20, demonstrating Qt's text handling capabilities, custom widgets, and application architecture. The editor will showcase modern C++ features while providing a familiar and intuitive interface.

## Core Features

### Basic Text Editing
- Multi-tab interface with closeable tabs
- Standard text operations (cut, copy, paste, undo, redo)
- File operations (new, open, save, save as)
- Search and replace functionality
- Line numbers display
- Status bar with cursor position and file information

### Advanced Features
- Syntax highlighting for common programming languages (C++, Python, JavaScript, etc.)
- Auto-indentation and bracket matching
- Zoom in/out functionality
- Word wrap toggle
- Recent files menu
- Session management (restore tabs on startup)

### Modern UI Elements
- Customisable themes (light/dark mode)
- Dockable panels for file explorer
- Find and replace panel
- Preferences dialog
- Drag and drop file support

## Technical Architecture

### Core Classes Structure

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

### Modern C++20 Features Integration

- **Concepts**: Template constraints for file type handlers
- **Ranges**: File processing and text manipulation
- **Coroutines**: Asynchronous file operations (Qt 6.5+)
- **Smart Pointers**: Memory management throughout
- **Structured Bindings**: Qt container operations
- **std::format**: String formatting (where supported)

### Key Qt Components

- **QMainWindow**: Main application window
- **QTabWidget**: Tab management
- **QTextEdit**: Text editing with custom subclass
- **QSyntaxHighlighter**: Syntax highlighting
- **QFileSystemModel**: File explorer
- **QSettings**: Configuration persistence
- **QAction**: Menu and toolbar actions
- **QShortcut**: Keyboard shortcuts

## Development Phases

### Phase 1: Foundation (Week 1)
- Set up Qt project structure
- Implement basic MainWindow with menu bar
- Create custom TextEditor class
- Add basic file operations (new, open, save)
- Implement tab management

### Phase 2: Core Editing Features (Week 2)
- Add standard editing operations
- Implement search functionality
- Create status bar with file information
- Add line numbers display
- Implement recent files menu

### Phase 3: Advanced Text Features (Week 3)
- Develop syntax highlighting system
- Add auto-indentation
- Implement bracket matching
- Create find and replace panel
- Add zoom functionality

### Phase 4: UI Polish & Settings (Week 4)
- Implement themes and customisation
- Add file explorer dock widget
- Create preferences dialog
- Add drag and drop support
- Implement session management

## File Structure

```
TextEditor/
├── CMakeLists.txt
├── main.cpp
├── src/
│   ├── MainWindow.{h,cpp}
│   ├── TextEditor.{h,cpp}
│   ├── TabWidget.{h,cpp}
│   ├── SyntaxHighlighter.{h,cpp}
│   ├── FileExplorer.{h,cpp}
│   ├── FindReplacePanel.{h,cpp}
│   ├── SettingsManager.{h,cpp}
│   └── Utils.{h,cpp}
├── resources/
│   ├── icons/
│   ├── themes/
│   └── application.qrc
└── docs/
    └── README.md
```

## Dependencies

### Required
- Qt 6.4+ (Core, Widgets, GUI)
- CMake 3.16+
- C++20 compatible compiler (GCC 10+, Clang 12+)

### Optional
- Qt 6.5+ for coroutines support
- QScintilla for advanced text editing features

## Building on Ubuntu 24.04

```bash
# Install dependencies
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential

# Build project
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

## Key Learning Outcomes

### Qt Framework
- Understanding Qt's signal-slot mechanism
- Model-view architecture with file systems
- Custom widget development
- Resource management and theming
- Cross-platform application design

### Modern C++20
- Practical use of concepts and ranges
- Memory management with smart pointers
- Structured bindings for cleaner code
- Template metaprogramming for extensibility

### Software Architecture
- Separation of concerns
- Plugin-like architecture for syntax highlighters
- Configuration management
- Event-driven programming patterns

## Future Enhancements

- Plugin system for custom syntax highlighters
- Git integration
- Code folding
- Multi-cursor editing
- Terminal integration
- Project management features
- Collaborative editing support

## Success Metrics

- Clean, maintainable C++20 code
- Responsive UI with smooth interactions
- Proper memory management (no leaks)
- Cross-platform compatibility
- Extensible architecture for future features
- Comprehensive error handling