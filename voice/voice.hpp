#pragma once

#include <julius/juliuslib.h>
#undef min
#undef max
#include <iostream>
#include "tts.hpp"

namespace voice
{
  enum CALLBACK_TYPE {
    CALLBACK_RESULT,
    CALLBACK_SPEECH_READY,
    CALLBACK_SPEECH_START,
    _CALLBACK_LAST,
  }

  class voiceio
  {
	public:
    std::ostream vout;
    std::istream vin;

    voiceio();
    ~voiceio();

    void init(const std::string& voice_dir, const std::string& dic_dir, const std::string& jconfpath);
    void setCallback(CALLBACK_TYPE type, void* handler);

	private:
    void* _handlers[_CALLBACK_LAST];
    tts t;
  }
}
