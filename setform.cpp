#include "posture/posture.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace yamax;

int main(int argc, char *argv[])
{
  if(argc != 3) {
    std::cerr << "argment is not satisfied." << std::endl;
    return 1;
  }

  posture form(argv[1]);
  std::string formname(argv[2]);
  if(formname == "stand")
    form.stand();
  else
    form.setPosture(formname);
  return 0;
}
