#include "posture.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace yamax;

posture::posture(const std::string& rname) : servonum(getServonumFromJson(getJsonFromFile(rname))), joints(getBusnumFromJson(getJsonFromFile(rname)),getServonumFromJson(getJsonFromFile(rname)),getAddressFromJson(getJsonFromFile(rname)))
{
  _path = "/usr/share/actions/"+rname+"/";

  joints.setPWMFreq(50);

  picojson::value v  = getJsonFromFile(rname);
  const picojson::value::object& obj = v.get<picojson::object>()["map"].get<picojson::object>();
  for (picojson::value::object::const_iterator i = obj.begin();
       i != obj.end();
       ++i) {
    //std::cout << "mapping. servo: " << i->first.c_str()[0] << " num: " << i->second.get<double>() << std::endl;
    mapping[i->first.c_str()[0]] = (uint8_t)i->second.get<double>();
  }

  std::string standpath = v.get<picojson::object>()["stand"].get<std::string>();
  std::ifstream ifs(_path+standpath);
  std::string str;
  if (ifs.fail())
      throw std::runtime_error("Failed to open configuration file: " + _path+standpath);

  picojson::value standv;
  ifs >> standv;
  std::string err = picojson::get_last_error();
  if (err.empty() && standv.is<picojson::object>()){
    const picojson::value::object& obj = standv.get<picojson::object>();
    _stands.resize(servonum);
    for (picojson::value::object::const_iterator i = obj.begin();
         i != obj.end();
         ++i) {
      //std::cout << "Setting stand. servo: " << i->first.c_str()[0] << " num: " << (int)mapping[i->first.c_str()[0]] << " deg: " << i->second.get<double>() << std::endl;
      _stands[mapping[i->first.c_str()[0]]] = (uint8_t)i->second.get<double>();
    }
  }else{
    int j=0;
    ifs.seekg(0, std::ios_base::beg);
    while (getline(ifs, str))
    {
      std::string::size_type index = str.find("#");
      if (index != std::string::npos)
        str = str.substr(0, index);
      //std::cout << "Setting stand. num: " << j << " deg: " << str.c_str() << std::endl;
      _stands.push_back(atoi(str.c_str()));
      j++;
    }
    if(j > joints.getNumber())
      throw std::runtime_error("Servo number mismatch!");
  }
  ifs.close();
}

bool posture::setPosture(std::string post)
{
  if(!fileExists(_path+post)){
    if(!fileExists(_path+post+".f")){
      if(!fileExists(_path+post+".jf")){
        throw std::runtime_error("posture file not found");
      }else
        post+=".jf";
    }else
      post+=".f";
  }

  std::ifstream ifs(_path+post);
  std::string str;
  if (ifs.fail()){
      throw std::runtime_error("Couldn't open the posture file: "+_path+post);
  }

  picojson::value posv;
  ifs >> posv;
  std::string err = picojson::get_last_error();
  if (err.empty() && posv.is<picojson::object>()){
    const picojson::value::object& obj = posv.get<picojson::object>();
    _stands.resize(servonum);
    for (picojson::value::object::const_iterator i = obj.begin();
         i != obj.end();
         ++i) {
      //std::cout << "Setting posture. servo: " << i->first.c_str()[0] << " num: " << (int)mapping[i->first.c_str()[0]] << " deg: " << i->second.get<double>() << std::endl;
      joints[mapping[i->first.c_str()[0]]].setDegrees((int8_t)i->second.get<double>()+_stands[mapping[i->first.c_str()[0]]]);
    }
  }else{
    int j=0;
    ifs.seekg(0, std::ios_base::beg);
    while (getline(ifs, str))
    {
      std::string::size_type index = str.find("#");
      if (index != std::string::npos)
        str = str.substr(0, index);
      //std::cout << "Setting posture. num: " << j << " deg: " << str.c_str() << std::endl;
      joints[j].setDegrees(atoi(str.c_str())+_stands[j]);
      j++;
    }
    if(j > joints.getNumber())
      throw std::runtime_error("Servo number mismatch!");
  }
  ifs.close();
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
  if (! _vnow.is<picojson::object>()) {
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

    _vnow = v;
    jsonifs.close();
    return v;
  }else
    return _vnow;
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
