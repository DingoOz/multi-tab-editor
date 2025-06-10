# Multi-Tab Text Editor

A modern text editor built with Qt 6 and C++20.

![Qt Version](https://img.shields.io/badge/Qt-6.4+-blue)
![C++ Standard](https://img.shields.io/badge/C++-20-orange)

## Features

- **Multi-tab interface** with drag-and-drop support
- **Syntax highlighting** for C++, Python, JavaScript, and more
- **Find and replace** with regex support
- **File explorer** with dockable panel
- **Theme support** - Light and Dark themes
- **Session management** - restore tabs on startup
- **Auto-save** and crash recovery
- **Line numbers** and zoom controls

## Quick Start

### Requirements
- Qt 6.4+
- CMake 3.16+
- C++20 compatible compiler

### Ubuntu/Debian
```bash
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
```

### Building
```bash
git clone <repository-url>
cd multi-tab-editor
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
./MultiTabEditor
```

## Keyboard Shortcuts

| Action | Shortcut |
|--------|----------|
| New File | `Ctrl+N` |
| Open File | `Ctrl+O` |
| Save File | `Ctrl+S` |
| Find | `Ctrl+F` |
| Replace | `Ctrl+H` |
| Close Tab | `Ctrl+W` |
| Zoom In/Out | `Ctrl+±` |

## Usage

- **File Operations**: Use File menu or keyboard shortcuts
- **Multiple Tabs**: Open multiple files in separate tabs
- **Find/Replace**: Use `Ctrl+F` for search, `Ctrl+H` for replace
- **Themes**: Switch via View → Theme → Light/Dark/Auto
- **File Explorer**: Browse files in the left dockable panel

## License

MIT License - see LICENSE file for details.