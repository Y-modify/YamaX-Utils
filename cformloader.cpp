#include <iostream>
#include <fstream>
#include <string>
#include "physicalio/physicalio.hpp"

using namespace pio;

int main(int argc, char *argv[])
{
  if(argc != 2) {
    std::cerr << "argment is not satisfied." << std::endl;
    return 1;
  }

  servos ss = servos(1, 32, 0x40);
  ss.setPWMFreq(50);
  std::ifstream ifs(argv[1]);
  std::string str;

  if (ifs.fail())
      std::cerr << "Failed to open " << argv[1] << std::endl;
  int j=0;
  while (getline(ifs, str))
  {
    std::string::size_type index = str.find("#");
    if (index != std::string::npos)
      str = str.substr(0, index);
    servo s = ss[j];
    s.minPulseWidth = 0.5;
    s.maxPulseWidth = 2.5;
    s.setDegrees(atoi(str.c_str()));
    j++;
  }
  return 0;
}
