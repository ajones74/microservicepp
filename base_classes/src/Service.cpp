#include <iostream>

#include <Service.hpp>
#include <Pipeline.hpp>
#include <nlohmann/json.hpp>

namespace mspp {
   void Service::set_configuration( const json &config_json )
   {

   }

   void Service::make_pipe( const std::string &pipe_label )
   {

   }

   void Service::link_pipes( const std::string &from,
                              const std::string &to )
   {

   }

   void Service::link_pipes( const std::string &from,
                             Pipeline &to )
   {

   }

   void Service::link_pipes( Pipeline &from,
                             Pipeline &to )
   {

   }

   void Service::run( )
   {

   }

}
