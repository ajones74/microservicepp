#include <algorithm>
#include <iostream>


#include <Logging_service_pipelines.hpp>
#include <iterator>
#include <string>


namespace mspp {

   void Logging_service_client_pipe::connect( )
   {

   }

   void Logging_service_client_pipe::start( )
   {

   }

   void Logging_service_client_pipe::stop( )
   {

   }

   std::string Logging_service_client_pipe::pull( const std::string &format )
   {
      return std::string{ "Unimplemented" };
   }

   std::vector<std::byte> Logging_service_client_pipe::pull( )
   {
      std::string foo = "Unimplemented";

      std::vector<std::byte> bar;
      bar.reserve( foo.size() );
  
      std::transform( foo.begin(), foo.end(), std::back_inserter(bar), []( const char c) { return std::byte(c); } );
      return bar;
   }

   bool Logging_service_client_pipe::push( const std::string &format, const std::string &payload )
   {
      return true;
   }
   
   bool Logging_service_client_pipe::push( const std::vector<std::byte> &payload )
   {
      return true;
   }
}
