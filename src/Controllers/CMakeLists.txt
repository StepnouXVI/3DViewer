cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Controllers"
    VERSION 0.1.1
    DESCRIPTION "Controllers for 3DViewer"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(Models_DIR "../installs/Models/cmake")
#find_package(Models 0.1.1 CONFIG REQUIRED )
#
#set(Services_DIR "../installs/Services/cmake")
#find_package(Services 0.1.1 CONFIG REQUIRED)



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
    # Список директорий, в который библиотека будет искать свои внутренние заголовки
    ${CMAKE_CURRENT_SOURCE_DIR}/include/private
    ${CMAKE_CURRENT_SOURCE_DIR}/include/public
    PUBLIC
    # где другие проекты будут видеть библиотеки
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/public>
    # где внешние проекты будут искать публичные заголовки библиотеки
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