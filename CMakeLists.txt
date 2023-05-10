cmake_minimum_required(VERSION 3.4) # 指定cmake最小版本 
project(P5RTableEditorForChinese) # 设置项目名 

set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)