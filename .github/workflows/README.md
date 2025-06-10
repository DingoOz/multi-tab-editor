# GitHub Workflows

This directory contains GitHub Actions workflows for Continuous Integration (CI).

## Workflows

### `build-test.yml` - Build Verification
- **Trigger**: Push to main branches and PRs
- **Purpose**: Verify that each commit can be built successfully
- **Runners**: Ubuntu 20.04, 22.04, and latest
- **Tests**: 
  - Qt6 installation
  - CMake configuration
  - Build compilation
  - Executable verification
  - Basic functionality test

### `ci.yml` - Comprehensive CI
- **Trigger**: Push to main/develop and PRs
- **Purpose**: Full CI pipeline with multiple Qt versions
- **Features**:
  - Matrix builds (Qt 6.4.0, 6.5.0)
  - Debug and Release builds  
  - Code quality checks
  - Build artifacts
  - Static analysis tools

## Build Requirements

The workflows install these dependencies on Ubuntu:
- `qt6-base-dev` - Qt6 core development files
- `qt6-tools-dev` - Qt6 development tools
- `cmake` - Build system
- `build-essential` - GCC compiler and build tools
- `pkg-config` - Package configuration tool

## Badge Status

The README includes a build status badge that shows the current state of the `Build Test` workflow:
```
![Build Status](https://github.com/DingoOz/multi-tab-editor/workflows/Build%20Test/badge.svg)
```

This badge will show:
- ✅ **Passing** - All builds successful
- ❌ **Failing** - One or more builds failed
- 🟡 **Pending** - Builds in progress