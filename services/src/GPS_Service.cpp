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

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      // Create a pipeline to the LOGGING service. 
      Pipeline logging_pipe = Pipeline( "pipeline://./service/logging" );
     
      // Throws an exception on failure to connect.
      logging_pipe.connect();

      Pipeline config_pipe = Pipeline( "pipeline://./service/configuration?service=GPS?flow=both" );
     
      // Throws an exception on failure to connect.
      config_pipe.connect();

      // Pull a copy of the system-wide configuration from the 
      // configuration service as a JSON-structured document.
      json config_json = config_pipe.pull( );

      // All source sections support "fan out" interfaces, 
      // so this is the way to instrument a data source with a debug pipeline
      Pipeline data_pipe          = Pipeline( "pipeline://./section/source/serial?device=ttymxc0" );
      Pipeline debug_pipe         = Pipeline( "pipeline://./section/source/serial?device=ttymxc0" );

      // All sink sections support "fan in" interfaces.
      // This is the way to publish data from a debug pipeline -- change the "topic", though!
      Pipeline publish_data_pipe  = Pipeline( "pipeline://./section/sink/publish?topic=GPS/data" );
      Pipeline publish_debug_pipe = Pipeline( "pipeline://./section/sink/publish?topic=GPS/debug" );


      // Create our service...
      Service GPS_service = Service( "service://./service/GPS", 
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
