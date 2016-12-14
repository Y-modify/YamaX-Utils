#include "posture/posture.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace yamax;

void usage(){
  fprintf(stderr, "setaction - perform specified action\n");
  fprintf(stderr, "Usage: setaction action times [-d delay]\n");
  exit(-1);
}

int main(int argc, char *argv[])
{
  int delay = -1;

  char opt;
  opterr = 0;
  while ((opt = getopt(argc, argv, "d:")) != -1) {
    switch (opt) {
      case 'd':
          delay = atoi(optarg);
          break;
      default:
          usage();
          break;
    }
  }
  if(argc < 2) {
    usage();
  }

  posture form;
  std::string formname(argv[optind]);
  if(formname == "stand")
    form.stand();
  else {
    if(delay != -1)
      form.doAction(formname, atoi(argv[optind + 1]), delay);
    else
      form.doAction(formname, atoi(argv[optind + 1]));
  }
  return 0;
}
