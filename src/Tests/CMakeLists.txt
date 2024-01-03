cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Tests"
    VERSION 0.1.1
    DESCRIPTION "Tests for 3DViewer"
)


if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE sources_file
        "src/*.c"
)

find_package(Check)


if(Check_FOUND)
    add_executable(${PROJECT_NAME} ${sources_file})
    target_link_libraries(${PROJECT_NAME}
            PUBLIC
            Services
            ${CHECK_LIBRARIES}
    )
endif()
message(${CMAKE_C_COMPILER_ID})
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    include(CodeCoverage)
    append_coverage_compiler_flags_to_target(${PROJECT_NAME})
#    append_coverage_compiler_flags_to_target(
#            Services
#            Models
#    )
    setup_target_for_coverage_lcov(
            NAME test_coverage
            EXECUTABLE  ${PROJECT_NAME}
            DEPENDENCIES ${PROJECT_NAME}
#            EXCLUDE "*settings*"
    )
endif()



file(GLOB_RECURSE public_headers
        "includes/*.h"
)

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


