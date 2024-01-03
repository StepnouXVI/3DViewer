cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Views"
    VERSION 0.1.1
    DESCRIPTION "Views for 3DViewer"
)


list(APPEND QT_MODULES Core Gui Widgets OpenGL OpenGLWidgets)
find_package(Qt6 COMPONENTS ${QT_MODULES} REQUIRED)
find_package(OpenGL REQUIRED)

set(QT_PREFIXED_MODULES ${QT_MODULES})
list(TRANSFORM QT_PREFIXED_MODULES PREPEND "Qt6::")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_library(${PROJECT_NAME} STATIC)


# file(GLOB public_headers "includes/*.h")


file(GLOB_RECURSE sources_file
        "src/*.cpp"
        "includes/*.cpp"
        "includes/*.h"
        "includes/*.h"
)

file(GLOB_RECURSE public_headers
        "includes/*.h"
)

target_sources(${PROJECT_NAME}
 PRIVATE
     ${sources_file})


target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE)
endif()

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Models
        Services
        Controllers
        ${QT_PREFIXED_MODULES}
)
