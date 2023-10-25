# Compile options

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RELEASE_FLAGS " \
  -O3 \
  -Wno-unused-parameter \
")

set(DEBUG_FLAGS " \
  -g \
  -O3 \
  -Wconversion \
  -Wshift-overflow \
  -Wno-unused-parameter \
  -Wcast-qual -Wcast-align \
  -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
  -D_FORTIFY_SOURCE=2 -fsanitize=address \
  -fsanitize=undefined -fno-sanitize-recover \
  -fstack-protector -Wno-format-nonliteral \
  -fno-omit-frame-pointer \
")

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} ${DEBUG_FLAGS}")

set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")
set (CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} ${RELEASE_FLAGS}")


add_compile_options(-W -Wall -Wextra -Wpedantic -g -fno-omit-frame-pointer)
