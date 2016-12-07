#include <iostream>
#include "libphysicalio/libphysicalio.hpp"
#include <unistd.h>

using namespace pio;

int main(void)
{
  servos ss = servos(1, 32, 0x40);
  ss.setPWMFreq(50);
  servo s = ss[27];
  s.minPulseWidth = 0.5; //MG90
  s.maxPulseWidth = 2.5; //MG90->2.3 SG90->2.5
  std::cout << "The number of servo is: "<< s.getNumber() << std::endl;
  std::cout << "Setting 0 to every degrees" << std::endl;
  for (;;)
  {
    for (int j = 0; j <= 180; j+=45){
      s.setDegrees(j);
      std::cout << j << std::endl;
      usleep(1000000);
    }
  }
  return 0;
}
