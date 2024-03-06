cmake_minimum_required(VERSION 3.0...3.27)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB SOURCES "*.cpp" "Figures/*.cpp")
file(GLOB HEADERS "*.h" "Figures/*.h")

include_directories(${DIR_SOURCES})

if(Qt${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    )
else()
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
                            Qt${QT_VERSION_MAJOR}::Widgets
                            Qt${QT_VERSION_MAJOR}::Core
                            Qt${QT_VERSION_MAJOR}::Gui)

# if(WIN32)
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND windeployqt ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}
#     )
# endif()
