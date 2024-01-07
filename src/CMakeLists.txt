cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("3DViewer"
    VERSION 0.9.1
    DESCRIPTION "3DViewer application" 
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CmakeModules)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

list(APPEND QT_MODULES Core Gui Widgets OpenGL OpenGLWidgets)
find_package(Qt6 COMPONENTS ${QT_MODULES} REQUIRED)
find_package(OpenGL REQUIRED)

set(QT_PREFIXED_MODULES ${QT_MODULES})
list(TRANSFORM QT_PREFIXED_MODULES PREPEND "Qt6::")

add_subdirectory(Models)
add_subdirectory(Services)
add_subdirectory(Controllers)
add_subdirectory(Views)


#CODE COVERAGE
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(CodeCoverage)
    append_coverage_compiler_flags_to_target(test)
    setup_target_for_coverage_lcov(
            NAME test_coverage
            EXECUTABLE test
            EXCLUDE ${CMAKE_BINARY_DIR}/* "${CMAKE_CURRENT_SOURCE_DIR}/Models/*" "${CMAKE_CURRENT_SOURCE_DIR}/Controllers/*" "/usr/local/*" "/usr/include/*"
            DEPENDENCIES test
    )
endif()



qt6_add_resources(RESOURCE_FILES resources.qrc)


qt_add_executable(${PROJECT_NAME} MACOSX_BUNDLE main.cpp ${RESOURCE_FILES})


# add_executable(${PROJECT_NAME} main.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets OpenGL::GL 3DViewer::Models 3DViewer::Controllers 3DViewer::Services 3DViewer::Views)
target_link_libraries(${PROJECT_NAME}
    PRIVATE

    ${QT_PREFIXED_MODULES}

    Views
    Models
    Services
    Controllers
)

add_subdirectory(third-party)

enable_testing()

add_subdirectory(Tests)
