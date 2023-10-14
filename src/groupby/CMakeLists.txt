set(LIB_TARGET groupby_lib)

get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)

file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.hpp)

set(LIB_SOURCES ${LIB_CXX_SOURCES} ${LIB_HEADERS})

add_library(${LIB_TARGET} STATIC ${LIB_SOURCES})
target_include_directories(${LIB_TARGET} PUBLIC ${LIB_INCLUDE_PATH})
