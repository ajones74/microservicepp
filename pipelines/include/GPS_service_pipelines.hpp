#ifndef _CONF_SERV_PIPELINE_HPP_
#define _CONF_SERV_PIPELINE_HPP_ 

#include <iostream>

#include <Pipeline.hpp>

namespace mspp {

   class GPS_service_data_pipe : public Pipeline 
   {
      public:
         GPS_service_data_pipe() = delete;
         GPS_service_data_pipe( const std::string &descriptive_string ) :
            Pipeline{ descriptive_string }
         { }

         virtual void connect( );

         // Pull a work-item from the end port of the pipeline
         // format/encoding specified in the string:
         //  "format=std::string"  (default)
         //  "format=JSON"
         //  "format=XML"
         //  "encode=UTF-8"
         //  "encode=UTF-32", etc.
         virtual std::string pull( const std::string &format);

         // Like the above function, but returns an unstructured 
         // std::string.
         virtual std::string pull( );

         virtual void add_source( std::unique_ptr< Section > section );

         virtual void add_section( std::unique_ptr< Section > section );

         virtual void add_sink( std::unique_ptr< Section > section );

      private:


   };
}
#endif // _CONF_SERV_PIPELINE_HPP_ 
