cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Services"
    VERSION 0.1.1
    DESCRIPTION "Services for 3DViewer"
)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_PREFIX_PATH "../installs/Models")
#set(Models_DIR "../installs/Models/cmake")

#find_package(Models 0.1.1 CONFIG REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)

qt6_add_resources(RESOURCE_FILES ../resources.qrc)


add_library(${PROJECT_NAME} STATIC
        src/OpenGL/SceneObjectOpenGLFactory.cpp
        src/OpenGL/SceneObjectOpenGL.cpp
        includes/Services/OpenGL/ShaderDrawer.h
        src/OpenGL/ShaderDrawer.cpp ${RESOURCE_FILES})

file(GLOB sources_file
            "src/*.cpp"
            "src/*.c"
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${sources_file}
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Models
        pcre
        ${QT_PREFIXED_MODULES}
        Qt6::Core
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


# without it public headers won't get installed
file(GLOB_RECURSE public_headers
        includes/*.h
)

file(GLOB_RECURSE sources_file
        src/*.cpp
        src/*.c
)


target_sources(${PROJECT_NAME}
    PRIVATE
    ${sources_file}
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

# where to find our CMake modules
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#message(STATUS "CMake module path: ${CMAKE_MODULE_PATH}")
#include(Installing)
