#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <string>
#include <vector>
#include <map>
#include <variant>

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
      Pipeline( const std::string &descriptive_string ) :
         m_descriptive_string{ descriptive_string },
         m_connected{ false }
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

      virtual void add_source( std::unique_ptr< Section> &&section );
      virtual void add_section( std::unique_ptr< Section> &&section  );
      virtual void add_sink( std::unique_ptr< Section> &&section );
   protected:
      //
      // MEMBERS
      // 
      std::string m_descriptive_string;
      bool m_connected;
     
      // There should really ever only be ONE source-section...
      //   * Use "std::vector::begin" iterator!
      // There should really ever only be ONE sink-section...
      //   * Use "std::vector::end" iterator! 
      std::vector< std::unique_ptr< Section > > m_sections;


   private:
};

}

#endif // _PIPELINE_HPP_
