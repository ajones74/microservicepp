#include <iostream>
#include <string>

#include <SLP_Parser.hpp>
#include <mspp_exceptions.hpp>

namespace mspp {
   void SLP_Parser::set( const std::string &conn_string )
   {
      m_connection_string = conn_string;
   }

   void SLP_Parser::parseable(  )
   {
      // First-level sanity check: look for the protocol 
      // delimiter, "://"
      const std::string protocol_delim{"://"};
      // Minimum string-length check.
      const std::string shortest_possible_string{ "service://" };


      if ( m_connection_string.length() < 
          shortest_possible_string.length( ) )
      {
         throw mspp_startup_exception( "connection string is too short." );
      }

      // Find the delimiter between protocol and host
      if ( m_connection_string.find( protocol_delim ) == std::string::npos  )
      {
         throw mspp_startup_exception( "missing/mal-formed protocol delimiter." );
      }
   }

   void SLP_Parser::tokenize_connection_string ( std::vector<std::string> &tokens )
   {

   }

   void SLP_Parser::tokenize_query_string( std::map<std::string, std::string> &map )
   {

   }

   std::string SLP_Parser::primary_resource( ) const
   {
      return std::string{"under construction"};
   }

   std::string SLP_Parser::secondary_resource( ) const
   {
      return std::string{"under construction"};
   }
   
}
