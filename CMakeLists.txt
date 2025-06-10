cmake_minimum_required(VERSION 3.16)

project(MultiTabEditor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    src/MainWindow.cpp
    src/TextEditor.cpp
    src/TabWidget.cpp
    src/SyntaxHighlighter.cpp
    src/FileExplorer.cpp
    src/FindReplacePanel.cpp
    src/SettingsManager.cpp
    src/Utils.cpp
)

set(HEADERS
    src/MainWindow.h
    src/TextEditor.h
    src/TabWidget.h
    src/SyntaxHighlighter.h
    src/FileExplorer.h
    src/FindReplacePanel.h
    src/SettingsManager.h
    src/Utils.h
)

qt_add_executable(MultiTabEditor ${SOURCES} ${HEADERS})

qt_add_resources(MultiTabEditor "application"
    PREFIX "/"
    FILES
        resources/icons/new.png
        resources/icons/open.png
        resources/icons/save.png
        resources/icons/cut.png
        resources/icons/copy.png
        resources/icons/paste.png
        resources/icons/undo.png
        resources/icons/redo.png
)

target_link_libraries(MultiTabEditor PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

if(WIN32)
    set_target_properties(MultiTabEditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()