cmake_minimum_required(VERSION 2.8)
add_subdirectory(physicalio)
add_library(posture SHARED
  posture.cpp
)
target_link_libraries(posture physicalio)

INSTALL(TARGETS posture LIBRARY DESTINATION lib)
INSTALL(FILES posture.hpp DESTINATION include/yamax)
