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
            m_descriptive_string{ descriptive_string }
         { }


         virtual void connect( );

         virtual std::string pull( const std::string &format);

         virtual std::string pull( );

         virtual void add_source( Section &section );

         virtual void add_section( Section &section );

         virtual void add_sink( Section &section );

      private:


   };
}
#endif // _CONF_SERV_PIPELINE_HPP_ 
