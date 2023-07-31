#ifndef _LOGGING_SERV_PIPELINE_HPP_
#define _LOGGING_SERV_PIPELINE_HPP_

#include <iostream>
#include <Pipeline.hpp>


namespace mspp {

   class Logging_service_client_pipe : public Pipeline {
      Logging_service_client_pipe( const std::string &descriptive_string) :
         Pipeline{ descriptive_string }
      { }

      virtual void connect( );

      virtual std::string pull( const std::string &format );

      virtual std::string pull( );

      virtual void add_source( Section &section );
      virtual void add_section( Section &section );
      virtual void add_sink( Section &section );
   }

   class Logging_service_server_pipe : public Pipeline {
  
   }


}

#endif  // _LOGGING_SERV_PIPELINE_HPP_ 
