#ifndef _CONF_SERV_PIPELINE_HPP_
#define _CONF_SERV_PIPELINE_HPP_ 

#include <iostream>

#include <Pipeline.hpp>

namespace mspp {

   class Configuration_service_client_pipe : public Pipeline 
   {
      public:
         Configuration_service_client_pipe() = delete;
         Configuration_service_client_pipe( const std::string &descriptive_string ) :
            Pipeline{ descriptive_string }
         { }


         virtual void connect( );
         virtual void start( );
         virtual void stop( );

         virtual std::string pull( const std::string &format);
         virtual std::vector<std::byte> pull( );

         virtual bool push( const std::string &format, const std::string &payload );
         virtual bool push( const std::vector<std::byte> &payload );
   };
}
#endif // _CONF_SERV_PIPELINE_HPP_ 
