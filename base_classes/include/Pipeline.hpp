#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <string>
#include <vector>
#include <map>

#include <Section.hpp>
#include <SLP_Parser.hpp>
#include <nlohmann/json.hpp>

#include <nng/nng.h>
#include <nng/protocol/pipeline0/push.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

namespace mspp {
class Pipeline {
   public:
      Pipeline( ) = delete;
      Pipeline( const std::string &descriptive_string ) :
         m_descriptive_string{ descriptive_string }
      { }

      virtual void connect( ) = 0;
      
      // Pull a work-item from the end port of the pipeline
      // format/encoding specified in the string:
      //  "format=std::string"  (default)
      //  "format=JSON"
      //  "format=XML"
      //  "encode=UTF-8"
      //  "encode=UTF-32", etc.
      virtual std::string pull( const std::string &format ) = 0;
      
      // Like the above function, but returns an unstructured 
      // std::string.
      virtual std::string pull( ) = 0;

      virtual void add_source( Section &section );
      virtual void add_section( Section &section );
      virtual void add_sink( Section &section );
   private:
      //
      // MEMBERS
      // 
      std::string m_descriptive_string;


};

}

#endif // _PIPELINE_HPP_
