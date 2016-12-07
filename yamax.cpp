#include <julius/juliuslib.h>
#undef min
#undef max
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <linux/kernel.h>
#include <unistd.h>
#include "simplerequest/sreq.hpp"
#include "physicalio/physicalio.hpp"
#include "openjtalk/tts.hpp"
#include "face/face.hpp"
#include "picojson.h"
#include "colors.h"

using namespace std;
using namespace pio;

uint8_t logLevel = 0;
const string APIKey = "786e715269793131796d36695275467667384430317154457a71626e32646953584657566c6d4c4370732e";
const string actionsPath = "/usr/share/actions/";
const string jconfPath = "/usr/share/julius/";
string tcontext;
servos ss = servos(1, 32, 0x40);
TextToSpeech tts("/usr/share/hts-voice/mei/mei_normal.htsvoice", "/usr/dic");
Face face("/usr/share/faces", "/home/root/.fonts/Kazesawa-Regular.ttf");

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

void performFromFile(string filename){
  std::ifstream ifs(actionsPath+filename);
  std::string str;

  if (ifs.fail()){
      message("Failed to open "+filename+"\n", ET_ERROR);
      return;
  }
  int j=0;
  while (getline(ifs, str))
  {
    std::string::size_type index = str.find("#");
    if (index != std::string::npos)
      str = str.substr(0, index);
    servo s = ss[j];
    s.minPulseWidth = 0.5;
    s.maxPulseWidth = 2.5;
    s.setDegrees(atoi(str.c_str()));
    j++;
  }
}

void actionHandler(string saying){
  if(string::npos != saying.find("こんにちは")){
    performFromFile("bow");
    usleep(900*1000);
  }else if(string::npos != saying.find("さよなら") || string::npos != saying.find("さようなら") || string::npos != saying.find("ちは") || string::npos != saying.find("こん") || string::npos != saying.find("どうも")){
    performFromFile("hi");
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
    performFromFile("stand");
  //}
}

static void status_recready(Recog *recog, void *dummy)
{
  if ((recog->jconf->input.speech_input == SP_MIC || recog->jconf->input.speech_input == SP_NETAUDIO) && !isTalking) {
    message("Ready\n", ET_INFO);
    face.setFace("normal");
    face.setMessage("準備完了");
  }
}

static void status_recstart(Recog *recog, void *dummy)
{
  if ((recog->jconf->input.speech_input == SP_MIC || recog->jconf->input.speech_input == SP_NETAUDIO) && !isTalking) {
    message("Recognition Started\n", ET_INFO);
    face.setFace("surprise");
    face.setMessage("認識開始");
  }
}

static void output_result(Recog *recog, void *dummy)
{
  int i, j;
  int len;
  WORD_INFO *winfo;
  WORD_ID *seq;
  int seqnum;
  int n;
  Sentence *s;
  RecogProcess *r;
  HMM_Logical *p;
  SentenceAlign *align;
  for(r=recog->process_list;r;r=r->next) {
    if (! r->live) continue;
    if (r->result.status < 0) {
      fprintf(stderr,"\n");
      continue;
    }

    /* output results for all the obtained sentences */
    winfo = r->lm->winfo;
    string usersay;

    for(n = 0; n < r->result.sentnum; n++) { /* for all sentences */

      s = &(r->result.sent[n]);
      seq = s->word;
      seqnum = s->word_num;

      for(i=0;i<seqnum;i++) {
        usersay += winfo->woutput[seq[i]];
      }
    }

    message("Result: "+usersay+"\n", ET_INFO);
    face.setMessage("認識: "+usersay);
    face.setFace("smile");
    message("Requesting to docomo API\n", ET_INFO);

    const list<string> headers{"Content-Type: application/json; charset=UTF-8"};
    sreq::request req("https://api.apigw.smt.docomo.ne.jp/dialogue/v1/dialogue?APIKEY="+APIKey,
                      "{\"utt\":\""+usersay+"\", \"context\":\""+tcontext+"\"}",
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
    tts.talk(botsay);
    isTalking = false;
    message("Handling specified actions...\n", ET_INFO);
    actionHandler(botsay);
  }
  fflush(stdout);
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
  ss.setPWMFreq(50);
  performFromFile("stand");

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
    jlog_set_output(NULL);
  }

  Jconf *jconf;
  Recog *recog;
  static char speechfilename[MAXPATHLEN];
  int ret;

  jconf = j_config_load_file_new((char*)((jconfPath+"/main.jconf").c_str()));
  j_config_load_file(jconf, (char*)((jconfPath+"/am-gmm.jconf").c_str()));
  if (jconf == NULL) {
    message("Cannot load voice recognition configuration\n", ET_ERROR);
    return -1;
  }

  recog = j_create_instance_from_jconf(jconf);
  if (recog == NULL) {
    message("Cannot create instance from jconf\n", ET_ERROR);
    return -1;
  }

  callback_add(recog, CALLBACK_EVENT_SPEECH_READY, status_recready, NULL);
  callback_add(recog, CALLBACK_EVENT_SPEECH_START, status_recstart, NULL);
  callback_add(recog, CALLBACK_RESULT, output_result, NULL);

  if (j_adin_init(recog) == FALSE) {
    return -1;
  }

  switch(j_open_stream(recog, NULL)) {
  case 0:			/* succeeded */
    break;
  case -1:      		/* error */
    message("Error in input stream\n", ET_ERROR);
    return -1;
  case -2:			/* end of recognition process */
    message("Failed to begin input stream\n", ET_ERROR);
    return -1;
  }

  message("<<< Julius ready >>>\n", ET_INFO);
  tts.talk("起動");

  ret = j_recognize_stream(recog);
  if (ret == -1) return -1;

  j_close_stream(recog);
  j_recog_free(recog);

  return 0;
}
