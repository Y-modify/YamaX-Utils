cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11 -finput-charset=UTF-8 -fexec-charset=UTF-8 -MT open_jtalk.o -MD -MP -MF ../../voice/open_jtalk-1.09/bin/.deps/open_jtalk.Po")

add_definitions(-DHAVE_CONFIG_H)
add_library(tts STATIC
  tts.cpp
)
#[[add_library(voice STATIC
  voice.cpp
)]]

#[[find_library(REQ_LIBRARY
    NAMES text2mecab mecab iconv mecab2njd njd njd_set_pronunciation njd_set_digit njd_set_accent_phrase njd_set_accent_type njd_set_unvoiced_vowel njd_set_long_vowel njd2jpcommon jpcommon
    PATHS ./open_jtalk-1.09/text2mecab/
          ../../openjtalk/open_jtalk-1.09/mecab/src/
          ../../openjtalk/open_jtalk-1.09/mecab2njd/
          ../../openjtalk/open_jtalk-1.09/njd/
          ../../openjtalk/open_jtalk-1.09/njd_set_pronunciation/
          ../../openjtalk/open_jtalk-1.09/njd_set_digit/
          ../../openjtalk/open_jtalk-1.09/njd_set_accent_phrase/
          ../../openjtalk/open_jtalk-1.09/njd_set_accent_type
          ../../openjtalk/open_jtalk-1.09/njd_set_unvoiced_vowel
          ../../openjtalk/open_jtalk-1.09/njd_set_long_vowel
          ../../openjtalk/open_jtalk-1.09/njd2jpcommon
          ./openjtalk/open_jtalk-1.09/jpcommon
)]]


target_link_libraries(tts
                      HTSEngine
                      stdc++
                      text2mecab mecab iconv mecab2njd njd njd_set_pronunciation njd_set_digit njd_set_accent_phrase njd_set_accent_type njd_set_unvoiced_vowel njd_set_long_vowel njd2jpcommon jpcommon)
