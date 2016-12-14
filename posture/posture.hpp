#pragma once

#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "picojson.h"
#include "physicalio/physicalio.hpp"

namespace yamax
{
  class posture
  {
  public:
      posture(const std::string& bpath = "/usr/share/yamax/");
      void setPosture(std::string post);
      void doAction(std::string act, uint16_t times, int delay = -1);
      void stand();
      uint16_t servonum;
      servos joints;
      std::map<char, uint8_t> mapping;

  private:
      picojson::value getJsonFromFile(const std::string& name);
      uint16_t getServonumFromJson(picojson::value v);
      uint8_t getBusnumFromJson(picojson::value v);
      uint8_t getAddressFromJson(picojson::value v);
      picojson::value _vnow;
      bool fileExists(const std::string& path);
      std::string _path;
      std::vector<uint8_t> _stands;
  };
}
