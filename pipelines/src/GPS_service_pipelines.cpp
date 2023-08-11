#include <iostream>

#include <GPS_service_pipelines.hpp>

#include <Serial_port_section.hpp>
#include <NMEA_0183_filters_section.hpp>
#include <Push_port_section.hpp>

namespace mspp 
{
   void GPS_service_data_pipe::connect( )
   {
      if ( m_connected )
      {
         return;
      }

      create_sections();

      for ( const auto & m : m_sections )
      {
         m->connect();
      }
      m_connected = true;
   }

   void GPS_service_data_pipe::start( )
   {

   }
   
   void GPS_service_data_pipe::stop( )
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

   // Throw a std::runtime_error or derived-class exception
   // if something goes sideways here.
   // 
   void GPS_service_data_pipe::create_sections( )
   {
      // Data source -- FROM the serial port.
      // TODO: The init-string should come from a configuration file
      //       or some other configuration source
      std::unique_ptr< Section > serial_port_section  = 
         std::make_unique< Serial_port_section >("ttymxc4?baud=115200&flow=none");

      // Data filter, 1 of 1 
      std::unique_ptr< Section > gps_frame_section = 
         std::make_unique< NMEA_0183_Framer_section >( " " );

      // Data sink -- 
      //  * ROLE    == LISTEN()
      //  * PATTERN == PUSH/SEND() 
      std::unique_ptr< Section > push_port_section =
         std::make_unique< Push_port_section >( " " );

      // Add the newly-minted sections to our pipeline...
      add_source( std::move( serial_port_section ) );
      add_section( std::move( gps_frame_section ) );
      add_sink( std::move( push_port_section ) );

   }

}
