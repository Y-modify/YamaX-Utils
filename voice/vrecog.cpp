#include "vrecog.hpp"
#include <utility>

using namespace yamax;

static void (*_handlers[_CALLBACK_VRECOG_LAST])(std::string);

vrecog::~vrecog(){
  j_request_terminate(_recog);
  _jconf = NULL;
  j_close_stream(_recog);
  _thread.join();
  j_recog_free(_recog);
}
void vrecog::loadJconfs(const std::vector<std::string>& jconfs)
{
  _jconf = j_config_load_file_new((char*)(jconfs[0].c_str()));
  for(uint16_t i=1; i<jconfs.size(); i++){
    j_config_load_file(_jconf, (char*)(jconfs[i].c_str()));
  }
  if (_jconf == NULL) {
    throw std::runtime_error("Cannot load voice recognition configuration");
  }
  _recog = j_create_instance_from_jconf(_jconf);
  if (_recog == NULL) {
    throw std::runtime_error("Cannot create instance from jconf");
  }
  callback_add(_recog, CALLBACK_EVENT_SPEECH_READY, recready, NULL);
  callback_add(_recog, CALLBACK_EVENT_SPEECH_START, recstart, NULL);
  callback_add(_recog, CALLBACK_RESULT, result, NULL);
}
void vrecog::setCallback(CALLBACK_TYPE type, void (*handler)(std::string)){
  _handlers[type] = handler;
}
void vrecog::start(){
  _thread = std::thread([&]() {
    if (j_adin_init(_recog) == FALSE) {
      throw std::runtime_error("Adin init failed");
    }
    switch(j_open_stream(_recog, NULL)) {
    case 0:			/* succeeded */
      break;
    case -1:      		/* error */
      throw std::runtime_error("Error in input stream");
    case -2:			/* end of recognition process */
      throw std::runtime_error("Failed to begin input stream");
    }
  	j_recognize_stream(_recog);
  });
}
void vrecog::pause(){
  j_request_pause(_recog);
}
void vrecog::resume(){
  j_request_resume(_recog);
}
void vrecog::setLogOutput(FILE *fp){
  jlog_set_output(fp);
}
void vrecog::recready(Recog *recog, void *dummy){
  if (recog->jconf->input.speech_input == SP_MIC || recog->jconf->input.speech_input == SP_NETAUDIO) {
    if(_handlers[CALLBACK_VRECOG_READY] != nullptr)
      (_handlers[CALLBACK_VRECOG_READY])("OK");
  }
}
void vrecog::recstart(Recog *recog, void *dummy){
  if (recog->jconf->input.speech_input == SP_MIC || recog->jconf->input.speech_input == SP_NETAUDIO) {
    if(_handlers[CALLBACK_VRECOG_START] != nullptr)
      _handlers[CALLBACK_VRECOG_START]("OK");
  }
}
void vrecog::result(Recog *recog, void *dummy){
  int i;
  WORD_INFO *winfo;
  WORD_ID *seq;
  int seqnum;
  int n;
  Sentence *s;
  RecogProcess *r;
  for(r=recog->process_list;r;r=r->next) {
    if (! r->live) continue;
    if (r->result.status < 0) {
      fprintf(stderr,"\n");
      continue;
    }

    /* output results for all the obtained sentences */
    winfo = r->lm->winfo;
    std::string usersay;

    for(n = 0; n < r->result.sentnum; n++) { /* for all sentences */

      s = &(r->result.sent[n]);
      seq = s->word;
      seqnum = s->word_num;

      for(i=0;i<seqnum;i++) {
        usersay += winfo->woutput[seq[i]];
      }
    }
    if(_handlers[CALLBACK_VRECOG_RESULT] != nullptr)
      _handlers[CALLBACK_VRECOG_RESULT](usersay);
  }
}
