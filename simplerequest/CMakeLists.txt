cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
add_library(simplerequest STATIC
  sreq.cpp
)
target_link_libraries(simplerequest curlpp curl m)
