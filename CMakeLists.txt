cmake_minimum_required(VERSION 3.4) # 指定cmake最小版本 
project(P5RTableEditorForChinese) # 设置项目名 

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} main.cpp
	"source/ChatLibrary.cpp"
	"source/ChatLibraryReader.cpp"
	"source/ChatReader.cpp"
	"source/CTDReader.cpp")