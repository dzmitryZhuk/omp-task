cmake_minimum_required(VERSION 3.0...3.27)

file(GLOB SOURCES "*.cpp")

include_directories(${DIR_SOURCES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    )