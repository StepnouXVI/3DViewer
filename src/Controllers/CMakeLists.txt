cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Controllers"
    VERSION 0.1.1
    DESCRIPTION "Controllers for 3DViewer"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)


file(GLOB_RECURSE LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")


target_sources(${PROJECT_NAME}
    PRIVATE
        ${LIB_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/private
    ${CMAKE_CURRENT_SOURCE_DIR}/include/public
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/public>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()


target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Models
        Services
)