cmake_minimum_required(VERSION 3.15)
project ( SortingTestSuite VERSION 1.0 LANGUAGES CXX )

#=== App target ===
set (APP_NAME "sortsuite")
# Prepare application to compile and link
add_executable( ${APP_NAME} main.cpp )
target_include_directories( ${APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set_target_properties( ${APP_NAME} PROPERTIES CXX_STANDARD 17 )
