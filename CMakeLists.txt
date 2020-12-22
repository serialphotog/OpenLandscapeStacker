cmake_minimum_required(VERSION 3.5)
project(OLS LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set paths correctly on Windows
if (WIN32)
  set(CMAKE_PREFIX_PATH "C:\\Qt\\6.0.0\\msvc2019_64\\")
endif()

# QT stuff
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lang/OLS_en_US.ts")

add_subdirectory(src)
