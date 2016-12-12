#include "voice/vrecog.hpp"
#include <iostream>
#include <string>

using namespace yamax;

void result(std::string res){
  std::cout << res << std::endl;
}

void ready(std::string res){
  std::cerr << "<< Please speak >>" << std::endl;
}

int main(){
  vrecog v;
  v.setLogOutput(NULL);
  v.loadJconfs({"/usr/share/julius/main.jconf", "/usr/share/julius/am-gmm.jconf"});
  v.setCallback(CALLBACK_VRECOG_RESULT, &result);
  v.setCallback(CALLBACK_VRECOG_READY, &ready);
  v.start();
  std::cerr << "Started" << std::endl;
  std::string line;
  getline(std::cin, line);
  return 0;
}
