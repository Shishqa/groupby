cmake_minimum_required(VERSION 3.18)

project(GroupBy)

include(cmake/CompileOptions.cmake)
include(cmake/CompileCommands.cmake)
include(cmake/Sanitize.cmake)

add_subdirectory(src)
add_subdirectory(tests)
