#include <iostream>
#include <string>
#include <list>
#include "simplerequest/sreq.hpp"
#include "picojson.h"

using namespace std;

int main(void){
  const string APIKey = "786e715269793131796d36695275467667384430317154457a71626e32646953584657566c6d4c4370732e";
  const list<string> headers{"Content-Type: application/json; charset=UTF-8"};
  string usersay;
  string tcontext;

  while(1){
    std::cerr << "> ";
    std::cin >> usersay;
    sreq::request req("https://api.apigw.smt.docomo.ne.jp/dialogue/v1/dialogue?APIKEY="+APIKey,
                      "{\"utt\":\""+usersay+"\", \"context\":\""+tcontext+"\"}",
                      headers);

    picojson::value v;
    std::string err = picojson::parse(v, req.result);
    if (! err.empty()) {
      std::cerr << err << std::endl;
      exit(1);
    }

    if (! v.is<picojson::object>()) {
      std::cerr << "JSON is not an object" << std::endl;
      exit(1);
    }

    tcontext = v.get<picojson::object>()["context"].to_str();
    std::cout << v.get<picojson::object>()["utt"].to_str() << std::endl;
  }

  return 0;
}
