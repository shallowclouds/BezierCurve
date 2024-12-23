# Installation Guide

## Prerequisites

### Required Software
- Qt Framework (version 4 or higher)
- Qt Creator IDE (recommended)
- C++ compiler compatible with your system
  - GCC (Linux)
  - MSVC (Windows)
  - Clang (macOS)

### System Requirements
- Operating System: Windows, Linux, or macOS
- Disk Space: At least 500MB for Qt and build files
- RAM: 2GB minimum recommended

## Installation Steps

### 1. Install Qt Framework
1. Download Qt from the official website: [Qt Downloads](https://www.qt.io/download)
2. During installation, ensure you select:
   - Qt Core
   - Qt GUI
   - Qt Widgets module
   - Development tools for your platform

### 2. Clone the Repository
```bash
git clone https://github.com/shallowclouds/BezierCurve.git
cd BezierCurve
```

### 3. Build the Project

#### Using Qt Creator (Recommended)
1. Open Qt Creator
2. Select "Open Project"
3. Navigate to the cloned repository
4. Open `src/SmoothCurveDemo.pro`
5. Configure the project for your kit
6. Click "Build Project" or press Ctrl+B (Cmd+B on macOS)

#### Using Command Line
1. Navigate to the project directory:
```bash
cd src
```

2. Generate Makefile:
```bash
qmake SmoothCurveDemo.pro
```

3. Build the project:
```bash
make  # On Linux/macOS
# or
nmake # On Windows with MSVC
```

### 4. Run the Application
- From Qt Creator: Click the "Run" button or press Ctrl+R
- From command line: Execute the built binary in the build directory

## Troubleshooting

### Common Issues

1. **Qt Modules Not Found**
   - Ensure Qt is properly installed
   - Check if required modules are installed
   - Verify PATH environment variable includes Qt binary directory

2. **Build Errors**
   - Verify Qt version (4 or higher required)
   - Check compiler compatibility
   - Ensure all dependencies are installed

3. **Runtime Errors**
   - Check if Qt libraries are in PATH
   - Verify Qt plugins are properly installed
   - Ensure write permissions in the build directory

### Getting Help
If you encounter issues not covered here:
1. Check Qt documentation
2. Review project issues on GitHub
3. Create a new issue with detailed error information

## Development Setup

### Recommended IDE Configuration
- Qt Creator settings:
  - Enable auto-formatting
  - Set indentation to spaces
  - Enable Qt Quick designer

### Building for Development
1. Clone with development branches:
```bash
git clone --branch develop https://github.com/shallowclouds/BezierCurve.git
```

2. Set up pre-commit hooks:
```bash
cp hooks/pre-commit .git/hooks/
chmod +x .git/hooks/pre-commit
```

3. Configure for debugging:
   - Build in debug mode
   - Enable Qt debugging helpers
   - Configure source maps
