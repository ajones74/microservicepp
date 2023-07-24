#include <iostream>
#include <vector>
#include <string>

#include <cstring>

/* 
{
  	"service": "GPS",
  	"config": {
  		"logging": 3,
  		"start": "WAITING"
  	},
  	"pipelines": [{
  			"pipeline": "SOURCE",
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
  			"pipeline": "DEBUG",
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
         "pipeline": "SINK",
         "sections" : [ {
               "pool": "nng?
            }
         ]
      }
  	]
}
*/

#include <nlohmann/json.hpp>
#include <nng/nng.h>
#include <nng/protocol/pipeline0/push.h>

#include <mspp_exceptions.hpp>


void example_of_using_nng( )
{
      nng_socket sock;
      int rv;
      char msg[2];

      std::cout << "PRE - Open the socket." << std::endl;
      if ((rv = nng_push0_open(&sock)) != 0) 
      {
         std::cout << "nng_push0_open" << rv ;
      }
      std::cout << "POST - Open the socket." << std::endl;
  

      std::cout << "PRE - DIAL the socket." << std::endl;
      if ((rv = nng_dial(sock, "...", NULL, 0)) != 0) 
      {
         std::cout << "nng_dial error(" << rv  << ")" << std::endl;
      }
      std::cout << "POST - DIAL the socket." << std::endl;

      // Interesting ... by default, nng_send(...) is a BLOCKING call!
      std::cout << "PRE - SEND the socket." << std::endl;
      if ((rv = nng_send(sock, msg, strlen(msg)+1, 0)) != 0)
      {
         std::cout << "nng_dial" << rv ;
      }
      std::cout << "POST - SEND the socket." << std::endl;
}



int main(int argc, const char **argv) 
{
   int exit_value = EXIT_SUCCESS;

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      // Connect a pipe to the LOGGING service. 
      // Pass it as the second arg to the service constructor
      Pipeline logging_pipe = Pipeline( "service:logging" );
      
      // this will throw an exception on failure to connect.
      logging_pipe.connect();

      // Connect a pipe to the CONFIG service, 
      // Pass it as the third arg to the service constructor
      Pipeline config_pipe = Pipeline( "service:configuration" );
     
      // this will throw an exception on failure to connect.
      config_pipe.connect()

      // Pull a copy of the system-wide configuration from the 
      // configuration service as a JSON-structured document.
      json config_json = config_pipe.pull( "format=JSON" );

      // Create our service...
      Service GPS_service = Service( "service:GPS", 
                                     logging_pipe, 
                                     config_pipe );
      GPS_service.set_configuration( config_json );

      // Find the description of the pipeline(s) in the confg_json object
      GPS_service.make_pipe( "GPS/SOURCE" );
      GPS_service.make_pipe( "GPS/DEBUG" );
      GPS_service.make_pipe( "GPS/SINK" );

      // Link the pipes meant for production
      GPS_service.link_pipes( "GPS/SOURCE", "GPS/SINK");
      // Link the pipes meant for debug/trace
      GPS_service.link_pipes( "GPS/DEBUG", logging_pipe );

      // This function never returns unless SIGKILL/SIGTERM/SIGABRT recv'd      
      GPS_service.run( );
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
