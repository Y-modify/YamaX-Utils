#include <unistd.h>
#include <iostream>
#include <string>
#include "voice/vrecog.hpp"
#include "posture/posture.hpp"
#include "simplerequest/sreq.hpp"
#include "voice/tts.hpp"
#include "face/face.hpp"
#include "picojson.h"
#include "colors.h"

using namespace yamax;
using namespace std;

vrecog v;
tts t("/usr/share/hts-voice/mei/mei_normal.htsvoice", "/usr/dic");
Face face("/usr/share/faces", "/home/root/.fonts/Kazesawa-Regular.ttf");
posture form("yamax32");

uint8_t logLevel = 0;
const string APIKey = "786e715269793131796d36695275467667384430317154457a71626e32646953584657566c6d4c4370732e";
string tcontext;
bool isTalking = false;

enum ERROR_TYPE{
  ET_ITERROR,
  ET_ERROR,
  ET_WARN,
  ET_INFO,
};

bool message(string message, ERROR_TYPE type)
{
  switch(type){
    case ET_ITERROR:
      cerr << COLOR_RED << COLOR_BOLD << "[ERROR] ";
      face.setMessage(message);
      break;
    case ET_ERROR:
      if(logLevel >= 1)
        cerr << COLOR_RED << "[ERROR] ";
      face.setMessage(message);
      break;
    case ET_WARN:
      if(logLevel >= 1)
        cerr << COLOR_YELLOW << "[WARN] ";
      break;
    case ET_INFO:
      if(logLevel >= 1)
        cerr << COLOR_GREEN << "[INFO] ";
      break;
  }
  if(logLevel >= 1)
    cerr << COLOR_DEFAULT << message;
  return true;
}

void actionHandler(string saying){
  if(string::npos != saying.find("こんにちは")){
    form.setPosture("bow");
    usleep(900*1000);
  }else if(string::npos != saying.find("さよなら") || string::npos != saying.find("さようなら") || string::npos != saying.find("ちは") || string::npos != saying.find("こん") || string::npos != saying.find("どうも")){
    form.setPosture("hi");
    usleep(900*1000);
  }/*else if(saying=="歩いて" || saying=="歩く" || saying=="歩け" || saying=="歩行"){
    for (i = 0; i < 5; i += 2)
      performFromFile("foot1");
      usleep(200*1000);
      performFromFile("walk1");
      usleep(200*1000);
      usleep(100*1000);
      performFromFile("foot2");
      usleep(200*1000);
      performFromFile("walk2");
      usleep(200*1000);
      usleep(100*1000);
    }*/
    form.stand();
  //}
}

void result(std::string res){
  if(isTalking)
   return;

  message("Result: "+res+"\n", ET_INFO);
  face.setMessage("認識: "+res);
  face.setFace("smile");
  message("Requesting to docomo API\n", ET_INFO);

  const list<string> headers{"Content-Type: application/json; charset=UTF-8"};
  sreq::request req("https://api.apigw.smt.docomo.ne.jp/dialogue/v1/dialogue?APIKEY="+APIKey,
                    "{\"utt\":\""+res+"\", \"context\":\""+tcontext+"\"}",
                    headers);

  picojson::value v;
  string err = picojson::parse(v, req.result);
  if (! err.empty()) {
    message(err+"\n", ET_ERROR);
    return;
  }

  if (! v.is<picojson::object>()) {
    message("JSON is not an object\n", ET_ERROR);
    return;
  }

  tcontext = v.get<picojson::object>()["context"].to_str();
  string botsay(v.get<picojson::object>()["utt"].to_str());
  message("Result: "+botsay+"\n", ET_INFO);
  face.setMessage("返答: "+botsay);
  isTalking = true;
  t.talk(botsay);
  isTalking = false;
  message("Handling specified actions...\n", ET_INFO);
  actionHandler(botsay);
}

void ready(std::string res){
  message("Ready\n", ET_INFO);
  face.setFace("normal");
  face.setMessage("準備完了");
}

void start(std::string res){
  if(!isTalking){
    message("Recognition Started\n", ET_INFO);
    face.setFace("surprise");
    face.setMessage("認識開始");
  }
}

int main(int argc, char *argv[]){
  char opt;
  opterr = 0;
  while ((opt = getopt(argc, argv, "v")) != -1) {
    switch (opt) {
      case 'v':
          logLevel++;
          break;
      default:
          fprintf(stderr, "YamaX 3.2 - based on Intel Edison with Julius %s & OpenJtalk\n", JULIUS_VERSION);
          fprintf(stderr, "Usage: %s [-v...]\n", argv[0]);
          return -1;
          break;
    }
  }

  face.setFace("unactive");
  form.stand();

  int cnt = 0;
  while(system("curl www.google.com &> /dev/null") != 0){
    message("Internet connection isn't established. Retrying...", ET_ERROR);
    cnt++;
    usleep(2000*1000);
    if(cnt > 5){
      message("Internet connection isn't established.", ET_ITERROR);
      return -1;
    }
  }

  if(logLevel < 2){
    v.setLogOutput(NULL);
  }

  v.loadJconfs({"/usr/share/julius/main.jconf", "/usr/share/julius/am-gmm.jconf"});
  v.setCallback(CALLBACK_VRECOG_RESULT, &result);
  v.setCallback(CALLBACK_VRECOG_START, &start);
  v.setCallback(CALLBACK_VRECOG_READY, &ready);
  v.start();

  message("<<< Julius ready >>>\n", ET_INFO);
  t.talk("起動");

  while(1);

  return 0;
}
