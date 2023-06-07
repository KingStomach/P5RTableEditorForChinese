cmake_minimum_required(VERSION 3.5)
project(P5RTableEditorForChinese LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/form")

include_directories("${PROJECT_SOURCE_DIR}/include")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
	main.cpp
	"form/mainwindow.ui"
	"include/mainwindow.h"
	"source/ChatLibrary.cpp"
	"source/mainwindow.cpp"
 "include/IWriter.h")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)