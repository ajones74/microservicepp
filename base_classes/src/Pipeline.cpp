#include <Pipeline.hpp>

#include <string>

namespace mspp {
   Pipeline::Pipeline ( const std::string &pipeline_string ) : m_pipeline_name{ pipeline_string }
   {
      
   }

   // throws a runtime exception if the connection
   // to a service or other pump fails.
   void connect( )
   {

   }

   // Pull the data from the pipeline in the specified format:
   //  * "format=JSON"
   //  * "format=XML"
   //  * "format=default"  (std::string)
   //  * "format=protobuf"  (google protobuf)
   //  * "format=msgpack"  
   std::string pull( const std::string &format )
   {
      std::string ret_val;

      return ret_val; 
   }
                                                               

      
}
