#ifndef  _GPS_SERV_PIPELINES_HPP_
#define  _GPS_SERV_PIPELINES_HPP_ 

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
         virtual void start( );
         virtual void stop( );

         // Pull a work-item from the end port of the pipeline
         // format/encoding specified in the string:
         //  "format=std::string"  (default)
         //  "format=JSON"
         //  "format=XML"
         //  "encode=UTF-8"
         //  "encode=UTF-32", etc.
         virtual std::string pull( const std::string &format );
         virtual std::vector<std::byte> pull( );

         virtual bool push( const std::string &format, const std::string &payload );
         virtual bool push( const std::vector<std::byte> &payload );
      private:
      // Called in the connect() method -- this method
      // _creates_ the sections and places them in the
      // "m_sections" container, above...
      void create_sections();


   };
}
#endif // _CONF_SERV_PIPELINE_HPP_ 
