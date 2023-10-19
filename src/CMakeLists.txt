add_subdirectory(groupby)
add_subdirectory(wheels)

set(CMD_TARGET group)

add_executable(${CMD_TARGET} main.cpp)
target_link_libraries(
  ${CMD_TARGET}
  PRIVATE groupby_lib
)
