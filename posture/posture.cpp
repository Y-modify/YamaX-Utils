#include "posture.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace yamax;

posture::posture(const std::string& rname) : joints(getBusnumFromJson(getJsonFromFile(rname)),getServonumFromJson(getJsonFromFile(rname)),getAddressFromJson(getJsonFromFile(rname)))
{
  _path = "/usr/share/actions/"+rname+"/";

  joints.setPWMFreq(50);

  std::string standpath = getJsonFromFile(rname).get<picojson::object>()["stand"].get<std::string>();
  std::ifstream ifs(_path+standpath);
  std::string str;
  if (ifs.fail())
      throw std::runtime_error("Failed to open configuration file: " + _path+standpath);

  int j=0;
  while (getline(ifs, str))
  {
    std::string::size_type index = str.find("#");
    if (index != std::string::npos)
      str = str.substr(0, index);
    _stands.push_back(atoi(str.c_str()));
    j++;
  }
  if(j > joints.getNumber())
    throw std::runtime_error("Servo number mismatch!");
}

bool posture::setPosture(std::string post)
{
  if(!fileExists(_path+post)){
    post += ".f";
    if(!fileExists(_path+post))
      return false;
  }
  std::ifstream ifs(_path+post);
  std::string str;

  if (ifs.fail()){
      return false;
  }
  int j=0;
  while (getline(ifs, str))
  {
    std::string::size_type index = str.find("#");
    if (index != std::string::npos)
      str = str.substr(0, index);
    joints[j].setDegrees(atoi(str.c_str())+_stands[j]);
    j++;
    if(j >= joints.getNumber())
     break;
  }
  return true;
}

void posture::stand(){
  for(uint16_t i=0; i<joints.getNumber(); i++){
    joints[i].setDegrees(_stands[i]);
  }
}

bool posture::fileExists(const std::string& path)
{
  struct stat st;
  return 0 == stat(path.c_str(), &st);
}

picojson::value posture::getJsonFromFile(const std::string& name)
{
  if (! vnow.is<picojson::object>()) {
    std::ifstream jsonifs("/usr/share/actions/"+name+"/robot.conf");
    if (jsonifs.fail())
      throw std::runtime_error("Failed to open configuration file: " + name);

    picojson::value v;
    jsonifs >> v;
    std::string err = picojson::get_last_error();
    if (! err.empty())
      throw std::runtime_error("Failed in parsing json: " + err);

    if (! v.is<picojson::object>())
      throw std::runtime_error("json isn't an object");

    vnow = v;
    return v;
  }else
    return vnow;
}

uint16_t posture::getServonumFromJson(picojson::value v)
{
  return v.get<picojson::object>()["board"].get<picojson::object>()["boards"].get<double>() * 16;
}
uint8_t posture::getBusnumFromJson(picojson::value v)
{
  return v.get<picojson::object>()["board"].get<picojson::object>()["bus"].get<double>();
}
uint8_t posture::getAddressFromJson(picojson::value v)
{
  return std::stoi(v.get<picojson::object>()["board"].get<picojson::object>()["address"].get<std::string>(), nullptr, 16);
}
