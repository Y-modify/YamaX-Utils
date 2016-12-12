#include "voice/tts.hpp"
#include <iostream>

using namespace yamax;

int main(int argc, char const* argv[])
{
  tts t(
		"/usr/share/hts-voice/mei/mei_normal.htsvoice",
		"/usr/dic"
	);
  if(argc == 2){
    t.talk(argv[1]);
    return 0;
  }
  std::string str;
  std::cin >> str;
  t.talk(str);
	return 0;
}
