#include <iostream>
#include <vector>
#include <string>
#include <variant>

/* 
{
  	"service": "GPS",
  	"config": {
  		"logging": 3,
  		"start": "WAITING"
  	},
  	"pipelines": [{
  			"pipeline": "from:",
  			"sections": [{
  					"pump": "serial?device=/dev/ttymxc4,baud=115200,parity=none,databits=8,stopbits=1,flow=none"
  				},
  				{
  					"frame": "NMEA 0183"
  				},
  				{
  					"filter": "NMEA 0138?ALLOW=$GPGGA,ALLOW=$GPMRC"
  				},
  				{
  					"decimate": 1.00
  				}
  			]
  		},
  		{
  			"pipeline": "from:",
  			"sections": [{
  					"pump": "serial?device=/dev/ttymxc4,baud=115200,parity=none,databits=8,stopbits=1,flow=none"
  				},
  				{
  					"frame": "NMEA 0183"
  				},
  				{
  					"pool": "file?file=/opt/tm/logging/gps.txt"
  				}
  			]
  		},
      {
         "pipeline": "to:",
         "sections" : [ {
               "pool": "nng?
            }
         ]
      }
  	]
}
*/

#include <nlohmann/json.hpp>

#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>
#include <Service.hpp>
#include <Section.hpp>

#include <Logging_service_pipelines.hpp>
#include <Configuration_service_pipelines.hpp>
#include <GPS_service_pipelines.hpp>

#include <Serial_port_section.hpp>
#include <NMEA_0183_filters_section.hpp>
#include <Push_port_section.hpp>




// NOTE: * The LOGGING SERVICE is the VERY FIRST SERVICE to launch.
//       * The CONFIGURATION SERVICE is the SECOND SERVICE to launch
//       * The FPCM SERVICE is the THIRD SERVICE to launch.
//       ** The FPCM SERVICE uses its discovery service in conjunction
//          with the configuration file fetched from the configuration 
//          service to launch other services such as:
//
//          * GPS Service
//          * IMU Service
//          * RFM Service, etc.
// 
int main(int argc, const char **argv) 
{
   int exit_value = EXIT_SUCCESS;

   const std::string our_service_name{"GPS Service" };

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      std::unique_ptr< Pipeline > logging_service_pipe = 
         std::make_unique< Logging_service_client_pipe>( our_service_name );
      // Throws an exception on failure to connect.
      logging_service_pipe->connect();

      std::unique_ptr< Pipeline > configuration_service_pipe = 
         std::make_unique< Configuration_service_client_pipe >( our_service_name );
      // Throws an exception on failure to connect.
      configuration_service_pipe->connect();

      // Pull a copy of the system-wide configuration from the 
      // configuration service as a JSON-structured document.
      json config_json = configuration_service_pipe->pull( "format=JSON" );

      // Data source
      std::unique_ptr< Section > serial_port_section  = 
         std::make_unique< Serial_port_section >("ttymxc4?baud=115200&flow=none");
      // Data filter, 1 of 1
      std::unique_ptr< Section > gps_frame_section = 
         std::make_unique< NMEA_0183_Framer_section >( " " );
      // Data sink
      //std::unique_ptr< Section > push_port_section =
      //   std::make_unique< Push_port_section >( " " );

      // Create a serial-port data pipeline specific to our service.
      // The ctor argument is any descriptive text string -- it's not 
      // parsed or used for anything other than a label.
      std::unique_ptr< Pipeline > our_service_pipe = 
         std::make_unique< GPS_service_data_pipe >( "GPS/Serial/ttymxc0" );
      // Add the newly-minted sections created just above to our Pipeline.
      our_service_pipe->add_source( serial_port_section );
      our_service_pipe->add_section( gps_frame_section );
      //our_service_pipe->add_sink( push_port_section );

      // Create our local GPS service...
      std::unique_ptr< Service > GPS_service = 
         std::make_unique< Service >( our_service_name );

      // Add Logging pipe, configuration pipe, and the data-pipe to the service.
      GPS_service->add( logging_service_pipe );
      GPS_service->add( configuration_service_pipe );
      GPS_service->add( our_service_pipe );

      // This calls the .start() methods (if applicable) for all 
      // associated pipes.
      GPS_service->start( );

      // This function never returns unless SIGKILL/SIGTERM/SIGABRT recv'd      
      GPS_service->run( );
   } 
   catch ( const mspp::mspp_startup_exception &e ) 
   {
      std::cout << "STARTUP ERROR(" << e.what() << ")" << std::endl;
      exit_value = EXIT_FAILURE;
   } 
   catch ( const std::runtime_error &e ) 
   {
      std::cout << "RUNTIME ERROR(" << e.what() << ")" << std::endl;
      exit_value = EXIT_FAILURE;
   } 
   catch ( const std::logic_error &e ) 
   {
      std::cout << "LOGIC ERROR(" << e.what() << ")" << std::endl;
      exit_value = EXIT_FAILURE;
   }
   catch ( ... )
   {
      std::cout << "UNHANDLED ERROR(" <<  ")" << std::endl;
      exit_value = EXIT_FAILURE;
   }
   std::cout << "EXITING" << std::endl;
   return exit_value; 
}
