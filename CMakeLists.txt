cmake_minimum_required(VERSION 3.30)

project(Tetris VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SRC_FILES
    src/main.cpp
    src/TWidget.h src/TWidget.cpp
    src/GameMap.h src/GameMap.cpp
    src/CMap.h src/CMap.cpp
    src/Figure.h src/Figure.cpp
    src/OFigure.h src/OFigure.cpp
    src/IFigure.h src/IFigure.cpp
    src/SFigure.h src/SFigure.cpp
    src/ZFigure.h src/ZFigure.cpp
    src/LFigure.h src/LFigure.cpp
    src/JFigure.h src/JFigure.cpp
    src/TFigure.h src/TFigure.cpp
    src/RandBlock.h src/RandBlock.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
    qt_add_executable(tetris MANUAL_FINALIZATION ${SRC_FILES})
else()
    message(FATAL_ERROR "Your Qt version is too old.")
endif()

target_include_directories(tetris PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(tetris PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(tetris PRIVATE Qt6::Core Qt6::Widgets)

########## INSTALLATION ##########
include(GNUInstallDirs)
install(TARGETS tetris
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET tetris
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

set_target_properties(tetris PROPERTIES MACOSX_BUNDLE TRUE)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tetris)
endif()
