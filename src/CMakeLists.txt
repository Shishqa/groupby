add_subdirectory(groupby)

set(CMD_TARGET group)

add_executable(${CMD_TARGET} main.cpp)
target_link_libraries(
  ${CMD_TARGET}
  PRIVATE groupby_lib
)
