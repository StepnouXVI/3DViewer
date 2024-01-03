cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Controllers"
    VERSION 0.1.1
    DESCRIPTION "Controllers for 3DViewer"
)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(Models_DIR "../installs/Models/cmake")
#find_package(Models 0.1.1 CONFIG REQUIRED )
#
#set(Services_DIR "../installs/Services/cmake")
#find_package(Services 0.1.1 CONFIG REQUIRED)



add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE sources_file
        src/*.cpp)

file(GLOB_RECURSE public_headers
        includes/*.h)

target_sources(${PROJECT_NAME}
    PRIVATE
      ${sources_file}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/${PROJECT_NAME}
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        # where external projects will look for the library's public headers
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