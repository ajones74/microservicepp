#include <iostream>
#include <vector>
#include <string>

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

      Pipeline* logging_service_pipe = 
         new Logging_service_client_pipe{ our_service_name };
      // Throws an exception on failure to connect.
      logging_service_pipe->connect();

      Pipeline *configuration_service_pipe = 
         new Configuration_service_client_pipe{ our_service_name };
      // Throws an exception on failure to connect.
      configuration_service_pipe->connect();

      // Pull a copy of the system-wide configuration from the 
      // configuration service as a JSON-structured document.
      json config_json = configuration_service_pipe->pull( );

      // Data source
      Section *serial_port_section  = 
         new Serial_port_section{"ttymxc4?baud=115200&flow=none"};
      // Data filter, 1 of 1
      Section *gps_frame_section = 
         new NMEA_0183_Framer_section;
      // Data sink
      Section *service_push_section   
         = new Service_push_section{ our_service_name };

      // Create a serial-port data pipeline specific to our service.
      Pipeline &our_service_pipe = new Service_server_pipe;
      // Add the newly-minted sections created just above to our Pipeline.
      our_service_pipe.add_source( serial_port_section );
      our_service_pipe.add_section( gps_frame_section );
      our_service_pipe.add_sink( service_push_section );

      // Create our local GPS service...
      Service &GPS_server = new Service( our_service_name );

      // Add Logging pipe, configuration pipe, and the data-pipe to the service.
      GPS_service.add( logging_service_pipe );
      GPS_service.add( configuration_service_pipe );
      GPS_service.add( our_service_pipe );

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
