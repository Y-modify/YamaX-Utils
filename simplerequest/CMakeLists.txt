cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
add_library(simplerequest SHARED
  sreq.cpp
)
target_link_libraries(simplerequest curlpp curl m)

INSTALL(TARGETS simplerequest LIBRARY DESTINATION lib)
INSTALL(FILES simplerequest.hpp DESTINATION include/yamax)
