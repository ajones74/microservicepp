#include <iostream>

#include <GPS_service_pipelines.hpp>

#include <Serial_port_section.hpp>
#include <NMEA_0183_filters_section.hpp>
#include <Push_port_section.hpp>

namespace mspp 
{
   void GPS_service_data_pipe::connect( )
   {
      if ( not m_connected )
      {
         // Data source
         std::unique_ptr< Section > serial_port_section  = 
            std::make_unique< Serial_port_section >("ttymxc4?baud=115200&flow=none");
         // Data filter, 1 of 1
         std::unique_ptr< Section > gps_frame_section = 
            std::make_unique< NMEA_0183_Framer_section >( " " );
         // Data sink
         std::unique_ptr< Section > push_port_section =
            std::make_unique< Push_port_section >( " " );

         // Add the newly-minted sections to our pipeline...
         add_source( std::move( serial_port_section ) );
         add_section( std::move( gps_frame_section ) );
         add_sink( std::move( push_port_section ) );

         m_connected = true;
      }
   }

   std::string GPS_service_data_pipe::pull( const std::string &format)
   {
      return std::string{ "Unimplemented" };
   }

   std::string GPS_service_data_pipe::pull( )
   {
      return std::string{ "Unimplemented" };
   }

}
