#pragma once

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace sreq{
  class request{
  public:
    string result;
    request( const string& url, const string& postdata=string(), const list<string>& header=list<string>());

  private:
     size_t writeMemoryCallback( char *ptr, size_t size, size_t nmemb  );
  };
}
