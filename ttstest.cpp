#include "voice/tts.hpp"

voice::tts t;

int main(int argc, char const* argv[])
{
	t.dload(
		"/usr/share/hts-voice/mei/mei_normal.htsvoice",
		"/usr/dic"
	);
	t.talk("ハローワールド!");
	return 0;
}
