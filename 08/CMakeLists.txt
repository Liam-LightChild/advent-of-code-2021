add_library(8.c common.cpp common.h)
add_executable(8.1 first.cpp)

target_link_libraries(8.1 8.c)
