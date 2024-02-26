cmake_minimum_required(VERSION 3.0...3.27)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB SOURCES "*.cpp")

include_directories(${DIR_SOURCES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    )

target_link_libraries(${PROJECT_NAME} PRIVATE -static
                            Qt5::Widgets
                            Qt5::Core
                            Qt5::Gui)

