cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11 -finput-charset=UTF-8 -fexec-charset=UTF-8 -MT open_jtalk.o -MD -MP -MF ../../voice/open_jtalk-1.09/bin/.deps/open_jtalk.Po")
set(CMAKE_SHARED_LINKER_FLAGS "-L../../voice/open_jtalk-1.09/text2mecab/ -L../../voice/open_jtalk-1.09/mecab/src/ -L../../voice/open_jtalk-1.09/mecab2njd/ -L../../voice/open_jtalk-1.09/njd/ -L../../voice/open_jtalk-1.09/njd_set_pronunciation/ -L../../voice/open_jtalk-1.09/njd_set_digit/ -L../../voice/open_jtalk-1.09/njd_set_accent_phrase/ -L../../voice/open_jtalk-1.09/njd_set_accent_type/ -L../../voice/open_jtalk-1.09/njd_set_unvoiced_vowel/ -L../../voice/open_jtalk-1.09/njd_set_long_vowel/ -L../../voice/open_jtalk-1.09/njd2jpcommon/ -L../../voice/open_jtalk-1.09/jpcommon/ -static")
add_definitions(-DHAVE_CONFIG_H)
#set(CMAKE_SHARED_LINKER_FLAGS "../../voice/open_jtalk-1.09/text2mecab/libtext2mecab.a ../../voice/open_jtalk-1.09/mecab/src/libmecab.a ../../voice/open_jtalk-1.09/mecab2njd/libmecab2njd.a ../../voice/open_jtalk-1.09/njd/libnjd.a ../../voice/open_jtalk-1.09/njd_set_pronunciation/libnjd_set_pronunciation.a ../../voice/open_jtalk-1.09/njd_set_digit/libnjd_set_digit.a ../../voice/open_jtalk-1.09/njd_set_accent_phrase/libnjd_set_accent_phrase.a ../../voice/open_jtalk-1.09/njd_set_accent_type/libnjd_set_accent_type.a ../../voice/open_jtalk-1.09/njd_set_unvoiced_vowel/libnjd_set_unvoiced_vowel.a ../../voice/open_jtalk-1.09/njd_set_long_vowel/libnjd_set_long_vowel.a ../../voice/open_jtalk-1.09/njd2jpcommon/libnjd2jpcommon.a ../../voice/open_jtalk-1.09/jpcommon/libjpcommon.a -static")

add_library(tts SHARED
  tts.cpp
)
add_library(vrecog SHARED
  vrecog.cpp
)

target_link_libraries(tts
                      HTSEngine
                      stdc++
                      iconv
                    text2mecab mecab mecab2njd njd njd_set_pronunciation njd_set_digit njd_set_accent_phrase njd_set_accent_type njd_set_unvoiced_vowel njd_set_long_vowel njd2jpcommon jpcommon)

target_link_libraries(vrecog
                      julius dl pthread sent asound z nsl m)

INSTALL(TARGETS tts LIBRARY DESTINATION lib)
INSTALL(FILES tts.hpp DESTINATION include/yamax)
INSTALL(TARGETS vrecog LIBRARY DESTINATION lib)
INSTALL(FILES vrecog.hpp DESTINATION include/yamax)
