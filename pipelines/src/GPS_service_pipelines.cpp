#include <iostream>

#include <GPS_service_pipelines.hpp>

namespace mspp 
{

   void GPS_service_data_pipe::connect( )
   {

   }

   std::string GPS_service_data_pipe::pull( const std::string &format)
   {
      return std::string{ "Unimplemented" };
   }

   std::string GPS_service_data_pipe::pull( )
   {
      return std::string{ "Unimplemented" };
   }

   void GPS_service_data_pipe::add_source( std::unique_ptr< Section > &&section )
   {
   
   }

   void GPS_service_data_pipe::add_section( std::unique_ptr< Section > &&section  )
   {

   }


   void GPS_service_data_pipe::add_sink( std::unique_ptr< Section >  &&section  )
   {
   
   }

}
