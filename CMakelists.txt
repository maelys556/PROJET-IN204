cmake_minimum_required(VERSION 3.0)
project(tetris)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Use PKG_CONFIG to get SDL2 and SDL2_image include and library paths
execute_process(COMMAND pkg-config --cflags sdl2 SDL2_image OUTPUT_VARIABLE SDL2_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND pkg-config --libs sdl2 SDL2_image OUTPUT_VARIABLE SDL2_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)



add_executable(Tetris main.cpp ${MY_SOURCES})
target_link_libraries(Tetris ${SDL2_LDFLAGS})

# Set compiler flags and include paths
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2_CFLAGS}")
target_include_directories(Tetris PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
include_directories(${SDL2_INCLUDE_DIRS})