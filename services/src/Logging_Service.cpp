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


int main(int argc, const char **argv) 
{
   int exit_value = EXIT_SUCCESS;

   const std::string our_service_name{"GPS Service" };

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      Pipeline* logging_pipe = new Logging_pipe{ our_service_name };
      // Throws an exception on failure to connect.
      logging_pipe->connect();

      Pipeline* configuration_pipe = new Configuration_pipe{ our_service_name };
      // Throws an exception on failure to connect.
      configuration_pipe->connect();

      // Pull a copy of the system-wide configuration from the 
      // configuration service as a JSON-structured document.
      json config_json = configuration_pipe->pull( );

      // Data source
      Section *serial_section    = new Serial_section{"ttymxc4?baud=115200&flow=none"};
      // Data filter, 1 of 1
      Section *gps_frame_section = new NMEA_0183_Framer_section;
      // Data sink
      Section *publish_section   = new Publisher_section{ our_service_name };

      // Create a data pipeline specific to our service, and add the newly-minted
      // sections.
      Pipeline *source_pipe = new Service_source_pipe{ our_service_name };

      source_pipe->begin_section( serial_section );
      source_pipe->add_section( gps_frame_section );
      source_pipe->end_section( publish_section );

      // Create our service...
      Service *GPS_service = new Service( config_json );

      GPS_service->add_pipeline ( logging_pipe );
      GPS_service->add_pipeline ( configuration_pipe );
      GPS_service->add_pipeline ( our_publishing_pipe );

      // This calls the .start() methods for all associated pipes.
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
