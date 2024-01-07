cmake_minimum_required(VERSION 3.15)

set(namespace "3DViewer")
project("Tests"
    VERSION 0.1.1
    DESCRIPTION "Tests for 3DViewer"
)


file(GLOB_RECURSE APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


target_link_libraries(${PROJECT_NAME} Services GTest::GTest)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})



