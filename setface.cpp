#include "face/face.hpp"
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace yamax;

Face face("/usr/share/faces", "/home/root/.fonts/Kazesawa-Regular.ttf");

int main( int argc, char *argv[] )
{
     try {
          /* Initialize DirectFB command line parsing. */
        face.setFace("smile");
        usleep(1000*1000);
        face.setFace("normal");
        usleep(1000*1000);
        face.setMessage("やあ");
     }
     catch (DFBException *ex) {
          /*
           * Exception has been caught, destructor of 'app' will deinitialize
           * anything at return time (below) that got initialized until now.
           */
          std::cerr << std::endl;
          std::cerr << "Caught exception!" << std::endl;
          std::cerr << "  -- " << ex << std::endl;
     }

     return 0;
}
