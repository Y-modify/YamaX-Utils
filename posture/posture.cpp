#include "posture.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace yamax;

posture::posture(const std::string& bpath) : servonum(getServonumFromJson(getJsonFromFile(bpath))), joints(getBusnumFromJson(getJsonFromFile(bpath)),getServonumFromJson(getJsonFromFile(bpath)),getAddressFromJson(getJsonFromFile(bpath)))
{
  _path = bpath;

  joints.setPWMFreq(50);

  picojson::value v  = getJsonFromFile(bpath);
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

void posture::setPosture(std::string post)
{
  post = "/postures/" + post + ".posture";
  if(!fileExists(_path+post))
      throw std::runtime_error("posture file not found: " + _path + post);

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
}

void posture::doAction(std::string act, uint16_t times, int delay){
  act = "/actions/" + act + ".action";
  if(!fileExists(_path+act))
      throw std::runtime_error("action file not found: " + _path + act);

  std::ifstream ifs(_path+act);
  std::string str;
  if (ifs.fail()){
      throw std::runtime_error("Couldn't open the action file: "+_path+act);
  }

  picojson::value actv;
  ifs >> actv;
  std::string err = picojson::get_last_error();
  if (!actv.is<picojson::object>())
    throw std::runtime_error("JSON isn't an object: "+_path+act);
  uint16_t defdel = (delay == -1) ? actv.get<picojson::object>()["default-delay"].get<double>() : delay;
  const picojson::value::array& obj = actv.get<picojson::object>()["flow"].get<picojson::value::array>();
  for(uint16_t j = 0; j<times; j++){
    for(auto i : obj){
      if(i.get<picojson::object>().find("perform") != i.get<picojson::object>().end()){
        setPosture(i.get<picojson::object>()["perform"].get<std::string>());
      }
      if(i.get<picojson::object>().find("delay") != i.get<picojson::object>().end()){
        std::string str2(i.get<picojson::object>()["delay"].get<std::string>());
        int ix = 0;
        while( (ix = str2.find("$", ix)) >= 0 ) {
            str2.replace(ix, strlen("$"), std::to_string(defdel));
        }
        usleep(std::stoi(str2)*1000);
      }
      //std::cout << "Setting motion. action: " << i.get<picojson::object>()["perform"].get<std::string>() << " sleep: " << str2 << std::endl;
    }
  }
  ifs.close();
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

picojson::value posture::getJsonFromFile(const std::string& path)
{
  if (! _vnow.is<picojson::object>()) {
    std::ifstream jsonifs(path+"/robot.conf");
    if (jsonifs.fail())
      throw std::runtime_error("Failed to open configuration file: " + path + "/robot.conf");

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
