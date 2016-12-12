cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
add_library(physicalio SHARED
  physicalio.cpp
)
target_link_libraries(physicalio mraa)

INSTALL(TARGETS physicalio LIBRARY DESTINATION lib)
INSTALL(FILES physicalio.hpp DESTINATION include/yamax)
