#include <iostream>
#include <string>

#include <SLP_Parser.hpp>
#include <mspp_exceptions.hpp>

namespace mspp {
   void SLP_Parser::set( const std::string &conn_string )
   {
      std::string shortest_possible_string{ "service://" };

      // A very primitive sanity check. Consider doing more...
      if ( conn_string.length() < shortest_possible_string.length( ) )
      {
         throw mspp_startup_exception( "connection string is too short." );
      }
      m_connection_string = conn_string;
   }

   void SLP_Parser::parseable(  )
   {
      // First-level sanity check: look for the protocol 
      // delimiter, "://" -- bail here if this is not
      // found. 
      const std::string protocol_delim{"://"};

   }

   void SLP_Parser::tokenize_connection_string ( std::vector<std::string> &tokens )
   {

   }

   void SLP_Parser::tokenize_query_string( std::map<std::string, std::string> &map )
   {

   }
}
