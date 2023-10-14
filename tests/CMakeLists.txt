include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

set(TEST_TARGET groupby_test)

get_filename_component(TEST_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(TEST_PATH "." ABSOLUTE)

file(GLOB_RECURSE TEST_CXX_SOURCES ${TEST_PATH}/*.cpp)
file(GLOB_RECURSE TEST_HEADERS ${TEST_PATH}/*.hpp)

set(TEST_SOURCES ${TEST_CXX_SOURCES} ${TEST_HEADERS})

add_executable(${TEST_TARGET} ${TEST_SOURCES})
target_link_libraries(
  ${TEST_TARGET}
  groupby_lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})
