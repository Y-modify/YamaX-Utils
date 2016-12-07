/* ----------------------------------------------------------------- */
/*           The Japanese TTS System "Open JTalk"                    */
/*           developed by HTS Working Group                          */
/*           http://open-jtalk.sourceforge.net/                      */
/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2008-2011  Nagoya Institute of Technology          */
/*                           Department of Computer Science          */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the HTS working group nor the names of its  */
/*   contributors may be used to endorse or promote products derived */
/*   from this software without specific prior written permission.   */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#include "tts.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <sstream>
#include <iostream>

#define MAXBUFLEN 1024

using namespace voice;

tts::tts()
	: wav_filename_(".__tmp__.wav")
{
  initialize(&open_jtalk);
}

tts::tts(const std::string& voice_dir, const std::string& dic_dir)
	: wav_filename_(".__tmp__.wav")
{
  /* initialize Open JTalk */
  initialize(&open_jtalk);

  /* load dictionary and HTS voice */
  if (load(&open_jtalk, (char*)(dic_dir.c_str()), (char*)(voice_dir.c_str())) != TRUE) {
     fprintf(stderr, "Error: Dictionary or HTS voice cannot be loaded.\n");
     exit(1);
  }
}

void tts::dload(const std::string& voice_dir, const std::string& dic_dir)
{
	if (load(&open_jtalk, (char*)(dic_dir.c_str()), (char*)(voice_dir.c_str())) != TRUE) {
		 fprintf(stderr, "Error: Dictionary or HTS voice cannot be loaded.\n");
		 exit(1);
	}
}

tts::~tts()
{
  Mecab_clear(&open_jtalk.mecab);
  NJD_clear(&open_jtalk.njd);
  JPCommon_clear(&open_jtalk.jpcommon);
  HTS_Engine_clear(&open_jtalk.engine);
}

void tts::initialize(Open_JTalk * open_jtalk_)
{
  Mecab_initialize(&open_jtalk_->mecab);
  NJD_initialize(&open_jtalk_->njd);
  JPCommon_initialize(&open_jtalk_->jpcommon);
  HTS_Engine_initialize(&open_jtalk_->engine);
}

bool tts::load(Open_JTalk * open_jtalk_, char *dn_mecab, char *fn_voice)
{
  if (Mecab_load(&open_jtalk_->mecab, dn_mecab) != TRUE) {
     return false;
  }
  if (HTS_Engine_load(&open_jtalk_->engine, &fn_voice, 1) != TRUE) {
     return false;
  }
  if (strcmp(HTS_Engine_get_fullcontext_label_format(&open_jtalk_->engine), "HTS_TTS_JPN") != 0) {
     return false;
  }
  return true;
}

bool tts::synthesis(const char *txt, FILE * wavfp)
{
  bool result = false;
  char buff[MAXBUFLEN];

  text2mecab(buff, txt);
  Mecab_analysis(&open_jtalk.mecab, buff);
  mecab2njd(&open_jtalk.njd, Mecab_get_feature(&open_jtalk.mecab),
            Mecab_get_size(&open_jtalk.mecab));
  njd_set_pronunciation(&open_jtalk.njd);
  njd_set_digit(&open_jtalk.njd);
  njd_set_accent_phrase(&open_jtalk.njd);
  njd_set_accent_type(&open_jtalk.njd);
  njd_set_unvoiced_vowel(&open_jtalk.njd);
  njd_set_long_vowel(&open_jtalk.njd);
  njd2jpcommon(&open_jtalk.jpcommon, &open_jtalk.njd);
  JPCommon_make_label(&open_jtalk.jpcommon);
  if (JPCommon_get_label_size(&open_jtalk.jpcommon) > 2) {
     if (HTS_Engine_synthesize_from_strings
         (&open_jtalk.engine, JPCommon_get_label_feature(&open_jtalk.jpcommon),
          JPCommon_get_label_size(&open_jtalk.jpcommon)) == TRUE)
        result = true;
     if (wavfp != NULL)
        HTS_Engine_save_riff(&open_jtalk.engine, wavfp);
     HTS_Engine_refresh(&open_jtalk.engine);
  }
  JPCommon_refresh(&open_jtalk.jpcommon);
  NJD_refresh(&open_jtalk.njd);
  Mecab_refresh(&open_jtalk.mecab);

  return result;
}

void tts::make_wav(const std::string& sentence)
{
	// 喋らせる言葉
	std::string s_talk_str = sentence;
	char *talk_str = &s_talk_str[0];

	// wav を用意
	FILE *wavfp = fopen(wav_filename_.c_str(), "wb");
	if (wavfp == NULL) {
		fprintf(stderr, "ERROR: Getfp() in &open_jtalk.c: Cannot open %s.\n", wav_filename_.c_str());
		return;
	}

	// wav を作成
	synthesis(&talk_str[0], wavfp);

	// wav を閉じる
	fclose(wavfp);
}

void tts::play_wav()
{
	/*Mix_Music *music;
	//Mix_Chunk *chunk;

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16LSB, 1, 4096);    // SDL_Mixerオープン

  music = Mix_LoadMUS(wav_filename_.c_str());
	//chunk = Mix_LoadWAV(wav_filename_.c_str());            // 効果音ファイル1をロード

  Mix_PlayMusic(music, -1);
	//Mix_PlayChannel( -1, chunk, 0 );            // 効果音1再生

	Mix_FreeMusic(music);
	//Mix_FreeChunk(chunk);                    // ロードした効果音1を開放
	Mix_CloseAudio();                        // SDL_Mixerクローズ*/
	system(("aplay --quiet "+wav_filename_).c_str());

}

void tts::stop()
{
	//Mix_HaltMusic();                        // 曲の再生停止
}

void tts::remove_wav() const
{
	remove( wav_filename_.c_str() );
}

void tts::talk(const std::string& str)
{
	//SDL_Init(SDL_INIT_AUDIO);                // SDL初期化

	make_wav(str);
	play_wav();
	remove_wav();

	//SDL_Quit();                                // SDL使用終了
}
