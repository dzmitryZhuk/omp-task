cmake_minimum_required(VERSION 3.0...3.27)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(painter
        VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
