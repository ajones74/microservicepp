#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <string>
#include <vector>

#include <Section.hpp>
#include <SLP_Parser.hpp>


namespace mspp {

class Pipeline {
   public:
      Pipeline( ) = delete;
      Pipeline( const std::string &connection_string );
      void connect( ); 
      std::string pull( );
      std::string pull( const std::string &format );

   private:
      //
      // MEMBERS
      // 
      std::string m_connection_string;
      std::vector<Section> m_sections;
      std::vector<std::string> m_conn_string_tokens;
      // All the key-value pairs found in the connection string
      // following the '?' delimiter.
      std::map<std::string, std::string> m_query_string_map;

      SLP_Parser m_parser;

      //
      // METHODS
      //
      void connect_to_service( );
      void connect_to_section( );

};

}

#endif // _PIPELINE_HPP_
