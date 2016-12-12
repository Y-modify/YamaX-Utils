#include <iostream>
#include <fstream>
#include "picojson.h"

int main(){
  std::string path("/usr/share/actions/yamax//robot.conf");
  std::ifstream ifs(path);
  if (ifs.fail())
      return false;

  picojson::value v;
  ifs >> v;
  std::string err = picojson::get_last_error();
  if (! err.empty()) {
    return false;
  }

  if (! v.is<picojson::object>()) {
    return false;
  }

  int servonum = v.get<picojson::object>()["board"].get<picojson::object>()["boards"].get<double>();
  int busnum = v.get<picojson::object>()["board"].get<picojson::object>()["bus"].get<double>();
  int address = std::stoi(v.get<picojson::object>()["board"].get<picojson::object>()["address"].get<std::string>(), nullptr, 16);

  std::cout << "servonum: " << servonum << std::endl << "busnum: " << busnum << std::endl << "address: " << std::hex << address << std::dec << std::endl;
  return 0;
}
