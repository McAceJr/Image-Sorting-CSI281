cmake_minimum_required(VERSION 3.26)

project(HelloRaylib VERSION 0.0.1 LANGUAGES CXX)

include(cmake/get_cpm.cmake)
include(cmake/compiler_check.cmake)

CPMAddPackage("gh:raysan5/raylib#5.5")
CPMAddPackage("gh:raysan5/raygui#4.0")
include_directories(${raygui_SOURCE_DIR}/src)
CPMAddPackage("gh:raysan5/rpng#1.0")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(HelloRaylib main.cpp)
target_link_libraries(HelloRaylib PUBLIC raylib)