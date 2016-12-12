#include "posture/posture.hpp"
#include <unistd.h>
#include <iostream>

yamax::posture post("yamax");

int main(){
  std::cout << "stand" << std::endl;
  post.stand();
  usleep(100000);
  std::cout << "bow" << std::endl;
  post.setPosture("bow");
  usleep(1000000);

  post.stand();
}
