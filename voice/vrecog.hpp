#pragma once

#include <julius/juliuslib.h>
#undef min
#undef max
#include <string>
#include <stdexcept>
#include <vector>
#include <thread>

namespace yamax
{
  enum CALLBACK_TYPE {
    CALLBACK_VRECOG_RESULT,
    CALLBACK_VRECOG_READY,
    CALLBACK_VRECOG_START,
    _CALLBACK_VRECOG_LAST,
  };

  class vrecog
  {
  public:
    ~vrecog();
    void loadJconfs(const std::vector<std::string>& jconfs);
    void setCallback(CALLBACK_TYPE type, void (*handler)(std::string));
    void setLogOutput(FILE *fp);
    void start();
    void pause();
    void resume();
  private:
    static void recready(Recog *recog, void *dummy);
    static void recstart(Recog *recog, void *dummy);
    static void result(Recog *recog, void *dummy);
    Jconf* _jconf;
    Recog* _recog;
    std::thread _thread;
  };
}
