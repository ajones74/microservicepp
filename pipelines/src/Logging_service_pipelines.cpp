#include <iostream>


#include <Logging_service_pipelines.hpp>


namespace mspp {

   void Logging_service_client_pipe::connect( )
   {

   }

   std::string Logging_service_client_pipe::pull( const std::string &format )
   {
      return std::string{ "Unimplemented" };
   }

   std::string Logging_service_client_pipe::pull( )
   {
      return std::string{ "Unimplemented" };
   }

   void Logging_service_client_pipe::add_source( Section &section )
   {

   }

   void Logging_service_client_pipe::add_section( Section &section )
   {

   }

   void Logging_service_client_pipe::add_sink( Section &section )
   {

   }
}
