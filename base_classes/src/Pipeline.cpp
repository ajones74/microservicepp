#include <iostream>
#include <string>

#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>
#include <SLP_Parser.hpp>



namespace mspp {

   Pipeline::Pipeline( const std::string &connection_string ) :
      m_connection_string{ connection_string }
   {
      m_parser.set( m_connection_string );
   }

   // throws a runtime exception if the connection
   // to a service or other pump fails.
   void Pipeline::connect( )
   {
      // Most primitive tests for a valid connection string
      m_parser.parseable( );

      // Decompose the connection string into constituent tokens
      m_parser.tokenize_connection_string( m_conn_string_tokens ); 

      // Parse the query string component (everything after the '?', just as if
      // the connection string were an HTTP URI) of the connection string
      // into a key-value map
      m_parser.tokenize_query_string( m_query_string_map );

      if (m_parser.service_or_section()

   }

   // Pull the data from the pipeline in the specified format:
   //  * "format=JSON"
   //  * "format=XML"
   //  * "format=default"  (std::string)
   //  * "format=protobuf"  (google protobuf)
   //  * "format=msgpack"  
   std::string Pipeline::pull( )
   {
      std::string ret_val;
      return ret_val; 
   }
   std::string Pipeline::pull( const std::string &format )
   {
      std::string ret_val;
      return ret_val; 
   }


}
