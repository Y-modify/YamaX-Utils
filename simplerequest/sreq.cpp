#include "sreq.hpp"

using namespace std;
using namespace cURLpp;
using namespace sreq;

request::request( const string& url, const string& postdata, const list<string>& header){
   Cleanup cleaner;
   Easy request;

   request.setOpt<Options::Url>(url);
   if(!postdata.empty()){
      request.setOpt<Options::PostFields>(postdata);
      request.setOpt<Options::PostFieldSize>(postdata.length());
   }
   if(!header.empty())
    request.setOpt<Options::HttpHeader>(header);

   request.setOpt<Options::WriteFunction>(Types::WriteFunctionFunctor(
         this, &request::writeMemoryCallback ));
   request.perform();
}

size_t request::writeMemoryCallback( char *ptr, size_t size, size_t nmemb  ){
  size_t realsize = size * nmemb;
  result.append( static_cast<const char *>(ptr), realsize );
  return realsize;
}
