cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wno-unused-variable")

set(CMAKE_VERBOSE_MAKEFILE 0)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(posture)
add_subdirectory(voice)
add_subdirectory(simplerequest)
add_subdirectory(face)

include_directories(/usr/include/directfb
                    /usr/include/++dfb)

add_executable(setface setface.cpp)
target_link_libraries(setface face)
add_executable(mkform mkform.cpp)
add_executable(setbaseform setbaseform.cpp)
target_link_libraries(setbaseform physicalio)
add_executable(setdeg setdeg.cpp)
target_link_libraries(setdeg physicalio)
add_executable(setform setform.cpp)
target_link_libraries(setform posture)
add_executable(docotalk docotalk.cpp)
target_link_libraries(docotalk simplerequest)

set(CMAKE_EXE_LINKER_FLAGS "-L../voice/open_jtalk-1.09/text2mecab/ -L../voice/open_jtalk-1.09/mecab/src/ -L../voice/open_jtalk-1.09/mecab2njd/ -L../voice/open_jtalk-1.09/njd/ -L../voice/open_jtalk-1.09/njd_set_pronunciation/ -L../voice/open_jtalk-1.09/njd_set_digit/ -L../voice/open_jtalk-1.09/njd_set_accent_phrase/ -L../voice/open_jtalk-1.09/njd_set_accent_type/ -L../voice/open_jtalk-1.09/njd_set_unvoiced_vowel/ -L../voice/open_jtalk-1.09/njd_set_long_vowel/ -L../voice/open_jtalk-1.09/njd2jpcommon/ -L../voice/open_jtalk-1.09/jpcommon/")

add_executable(vecho vecho.cpp)
target_link_libraries(vecho tts)
add_executable(vcat vcat.cpp)
target_link_libraries(vcat vrecog)

INSTALL(TARGETS vecho vcat setface mkform setbaseform setdeg setform docotalk RUNTIME DESTINATION bin)

#[[
add_executable(demo-servos demo-servos.cpp)
target_link_libraries(demo-servos physicalio)
add_executable(kusoran kusoran.cpp)
target_link_libraries(kusoran physicalio)
add_executable(postest postest.cpp)
target_link_libraries(postest posture)
add_executable(yamax yamax.cpp)
target_link_libraries(yamax posture tts simplerequest face vrecog)]]
