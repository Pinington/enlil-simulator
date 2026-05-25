cmake_minimum_required(VERSION 3.16)
project(Enlil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets OpenGL OpenGLWidgets)
qt_standard_project_setup()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

qt6_add_resources(RESOURCES resources.qrc)

add_executable(enlil
    main.cpp
    ${SOURCES}
    ${RESOURCES}
)

target_include_directories(enlil PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(enlil PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)