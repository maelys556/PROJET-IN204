# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# MY_SOURCES at CMakeLists.txt:7 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/guiscalbish/in204/src/*.cpp")
set(OLD_GLOB
  "/home/guiscalbish/in204/src/game.cpp"
  "/home/guiscalbish/in204/src/grid.cpp"
  "/home/guiscalbish/in204/src/interface.cpp"
  "/home/guiscalbish/in204/src/tetromino.cpp"
  "/home/guiscalbish/in204/src/textures.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/guiscalbish/in204/build/CMakeFiles/cmake.verify_globs")
endif()
