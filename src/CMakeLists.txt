add_subdirectory(groupby)

set(CMD_TARGET group)

add_executable(${CMD_TARGET} group.cpp)
target_link_libraries(
  ${CMD_TARGET}
  PRIVATE groupby_lib
)


set(CMD_TARGET generate)

add_executable(${CMD_TARGET} generate.cpp)
target_link_libraries(
  ${CMD_TARGET}
  PRIVATE groupby_lib
)
