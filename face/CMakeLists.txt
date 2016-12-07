cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")

include_directories(/usr/include/directfb
                    /usr/include/++dfb)

add_library(dfbimage STATIC
  dfbimage.cpp
)
add_library(face STATIC
  face.cpp
)

target_link_libraries(dfbimage directfb ++dfb)

target_link_libraries(face dfbimage directfb ++dfb)
