cmake_minimum_required(VERSION 3.26)
project(threadpool)

set(CMAKE_CXX_STANDARD 11)

#add_library(threadpool SHARED threadpool.h)

add_executable(test_pool test_pool.cpp threadpool.h)
#target_link_libraries(test_pool threadpool)
