#include <iostream>

#include <Configuration_service_pipelines.hpp>

namespace mspp 
{

   void Configuration_service_client_pipe::connect( )
   {

   }

   std::string Configuration_service_client_pipe::pull( const std::string &format)
   {
      return std::string{ "Unimplemented" };
   }

   std::string Configuration_service_client_pipe::pull( )
   {
      return std::string{ "Unimplemented" };
   }

   void Configuration_service_client_pipe::add_source( Section &section )
   {
   
   }

   void Configuration_service_client_pipe::add_section( Section &section )
   {

   }


   void Configuration_service_client_pipe::add_sink( Section &section )
   {
   
   }

}
