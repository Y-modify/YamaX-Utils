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

#pragma once

#include <string>
#include <vector>

/* openjtalk header */
/* Main headers */
#include "open_jtalk-1.09/mecab/src/mecab.h"
#include "open_jtalk-1.09/njd/njd.h"
#include "open_jtalk-1.09/jpcommon/jpcommon.h"
#include "HTS_engine.h"

/* Sub headers */
#include "open_jtalk-1.09/text2mecab/text2mecab.h"
#include "open_jtalk-1.09/mecab2njd/mecab2njd.h"
#include "open_jtalk-1.09/njd_set_pronunciation/njd_set_pronunciation.h"
#include "open_jtalk-1.09/njd_set_digit/njd_set_digit.h"
#include "open_jtalk-1.09/njd_set_accent_phrase/njd_set_accent_phrase.h"
#include "open_jtalk-1.09/njd_set_accent_type/njd_set_accent_type.h"
#include "open_jtalk-1.09/njd_set_unvoiced_vowel/njd_set_unvoiced_vowel.h"
#include "open_jtalk-1.09/njd_set_long_vowel/njd_set_long_vowel.h"
#include "open_jtalk-1.09/njd2jpcommon/njd2jpcommon.h"

/*#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>*/

/**
 * Open JTalkでTTSするクラス
 */
namespace voice{
	class tts
	{
	public:
		/**
		 * OpenJTalkに渡すパラメータを生成
		 * @param[in] voice_dir	音素などが入ったディレクトリ
		 * @param[in] dic_dir	辞書入ったディレクトリ
		 */
		tts();
		tts(const std::string& voice_dir, const std::string& dic_dir);

		/**
		 * デストラクタ
		 */
		~tts();

		void dload(const std::string& voice_dir, const std::string& dic_dir);

		/**
		 * 喋らせる
		 * @param[in] str	喋らせる文章
		 */
		void talk(const std::string& str);

		/**
		 * 喋りをストップする
		 */
		void stop();

	private:
		/**
		 * Open JTalk に必要な情報をまとめておく構造体
		 */
	  struct Open_JTalk {
	 	   Mecab mecab;
	 	   NJD njd;
	 	   JPCommon jpcommon;
	 	   HTS_Engine engine;
	 	} open_jtalk;

		//! OpenJTalk を指定されたパラメタで初期化する(open_jtalk.c より抜粋)
		void initialize(Open_JTalk * open_jtalk);

		//! 必要なファイル群をロードする(open_jtalk.c より抜粋)
		bool load(Open_JTalk * open_jtalk, char *dn_mecab, char *fn_voice);

		//! 指定したテキストを喋る wav ファイルを作成する
		bool synthesis(const char *txt, FILE * wavfp);

		/**
		 * パラメタなどを整形して synthesis を実行する
		 * @param[in] sentence	喋らせる文章
		 */
		//!
		void make_wav(const std::string& sentence);

		//! wav ファイルを再生する
		void play_wav();

		//! wav ファイルを削除する
		void remove_wav() const;

		//! 出力wavファイル名
		const std::string wav_filename_;

		//! 再生中の wav
		//ALuint wav_src_;
	};
}
