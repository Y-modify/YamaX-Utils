#include <iostream>
#include "physicalio/physicalio.hpp"

using namespace std;
using namespace pio;

int main(int argc, char *argv[])
{
  if(argc != 3) {
    cout << "argment is not satisfied" << endl;
    return 1;
  }
  servos ss = servos(1, 32, 0x40);
  ss.setPWMFreq(50);
  servo s = ss[atoi(argv[1])];
  cout << "set number " << atoi(argv[1]) << " to " << atoi(argv[2]) << endl;
  s.minPulseWidth = 0.5; //MG90
  s.maxPulseWidth = 2.3; //MG90
  s.setDegrees(atoi(argv[2]));
  return 0;
}
