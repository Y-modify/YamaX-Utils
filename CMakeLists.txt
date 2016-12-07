cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -g -std=c++11 -O2 -Wno-unused-variable -DDEBUG")
set(CMAKE_VERBOSE_MAKEFILE 0)

add_subdirectory(physicalio)
add_subdirectory(voice)
add_subdirectory(simplerequest)
add_subdirectory(face)

include_directories(/usr/include/directfb
                    /usr/include/++dfb)

link_directories(../voice/open_jtalk-1.09/text2mecab/
                ../voice/open_jtalk-1.09/mecab/src/
                ../voice/open_jtalk-1.09/mecab2njd/
                ../voice/open_jtalk-1.09/njd/
                ../voice/open_jtalk-1.09/njd_set_pronunciation/
                ../voice/open_jtalk-1.09/njd_set_digit/
                ../voice/open_jtalk-1.09/njd_set_accent_phrase/
                ../voice/open_jtalk-1.09/njd_set_accent_type
                ../voice/open_jtalk-1.09/njd_set_unvoiced_vowel
                ../voice/open_jtalk-1.09/njd_set_long_vowel
                ../voice/open_jtalk-1.09/njd2jpcommon
                ../voice/open_jtalk-1.09/jpcommon)

add_executable(docotalk docotalk.cpp)
target_link_libraries(docotalk simplerequest)

add_executable(demo-servos demo-servos.cpp)
target_link_libraries(demo-servos physicalio)

add_executable(setdeg setdeg.cpp)
target_link_libraries(setdeg physicalio)

add_executable(actions-example actions-example.cpp)
target_link_libraries(actions-example physicalio)

add_executable(ttstest ttstest.cpp)
target_link_libraries(ttstest tts)

add_executable(cformloader cformloader.cpp)
target_link_libraries(cformloader physicalio)

add_executable(faceset faceset.cpp)
target_link_libraries(faceset face)

add_executable(yamax yamax.cpp)
target_link_libraries(yamax physicalio tts simplerequest face julius dl pthread sent asound z nsl m)
