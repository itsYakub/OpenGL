cmake_minimum_required(VERSION 3.11)

project(opengl C)

# Building the libopengl.a library
add_subdirectory(${CMAKE_SOURCE_DIR}/opengl)

# Building the library samples
add_subdirectory(${CMAKE_SOURCE_DIR}/samples)
