#include <iostream>
#include "posture/physicalio/physicalio.hpp"

using namespace std;
using namespace yamax;

int main(int argc, char *argv[])
{
  if(argc != 3) {
    cout << "argment is not satisfied" << endl;
    return 1;
  }
  servos ss = servos(1, 32, 0x40);
  ss.setPWMFreq(50);
  cout << "set number " << atoi(argv[1]) << " to " << atoi(argv[2]) << endl;
  ss[atoi(argv[1])].setDegrees(atoi(argv[2]));
  return 0;
}
