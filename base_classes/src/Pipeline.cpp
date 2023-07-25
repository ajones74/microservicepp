#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>
#include <SLP_Parser.hpp>

#include <string>


namespace mspp {

   Pipeline::Pipeline( const std::string &connection_string ) :
      m_connection_string{ connection_string }
   {
   }

   // throws a runtime exception if the connection
   // to a service or other pump fails.
   void Pipeline::connect( )
   {
      SLP_Parser parser;

      parser.parseable( m_connection_string );

   }

   // Pull the data from the pipeline in the specified format:
   //  * "format=JSON"
   //  * "format=XML"
   //  * "format=default"  (std::string)
   //  * "format=protobuf"  (google protobuf)
   //  * "format=msgpack"  
   std::string Pipeline::pull( const std::string &format )
   {
      std::string ret_val;
      return ret_val; 
   }
}
