#include "posture/posture.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace yamax;

int main(int argc, char *argv[])
{
  if(argc != 2) {
    std::cerr << "argment is not satisfied." << std::endl;
    return 1;
  }

  posture form;
  std::string formname(argv[1]);
  if(formname == "stand")
    form.stand();
  else
    form.setPosture(formname);
  return 0;
}
