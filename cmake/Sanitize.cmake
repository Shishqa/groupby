# Address Sanitizer
# https://clang.llvm.org/docs/AddressSanitizer.html

set(ASAN_COMPILE_FLAGS -fsanitize=address,undefined -fno-sanitize-recover=all)
set(ASAN_LINK_FLAGS -fsanitize=address,undefined)

if(ASAN)
    ProjectLog("Sanitize with address sanitizer")
    add_compile_options(${ASAN_COMPILE_FLAGS})
    add_link_options(${ASAN_LINK_FLAGS})
endif()
