cmake_minimum_required(VERSION 3.0...3.27)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt REQUIRED COMPONENTS Core Gui)

file(GLOB SOURCES "*.cpp")

include_directories(${DIR_SOURCES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    )

target_link_libraries(${PROJECT_NAME}
                            Qt5::Widgets)
