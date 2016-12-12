#pragma once

#include <string>
#include <vector>
#include "picojson.h"
#include "physicalio/physicalio.hpp"

namespace yamax
{
  class posture
  {
  public:
      posture(const std::string& rname);
      bool setPosture(const std::string post);
      void stand();
      servos joints;

  private:
      picojson::value getJsonFromFile(const std::string& name);
      uint16_t getServonumFromJson(picojson::value v);
      uint8_t getBusnumFromJson(picojson::value v);
      uint8_t getAddressFromJson(picojson::value v);
      picojson::value vnow;
      bool fileExists(const std::string& path);
      std::string _path;
      std::vector<uint8_t> _stands;
  };
}
