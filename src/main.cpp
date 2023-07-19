#include <iostream>

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

#include <services/pipe.hpp>


int main(int argc, const char **argv) 
{

   try 
   {
      using namespace mspp;

      // Connect a pipe to the LOGGING service.
      Pipeline logging_pipe = Pipeline( "service:logging" );

      // Connect a pipe to the CONFIG service, 
      // fetch the configuration in a JSON structured document 
      Pipeline config_pipe = Pipeline( "service:configuration?format=JSON" );

      // Pull one ojject (A JSON doc) from the pipeline
      json config_json = config_pipe.pull();


      Service GPS_service = Service( "service:GPS" );


      GPS_service.connect_pipe( logging_pipe );
      GPS_service.connect_pipe( config_pipe );
      GPS_service.make_pipe( config_json, "GPS/SOURCE" );
      GPS_service.make_pipe( config_json, "GPS/DEBUG" );
      GPS_service.make_pipe( config_json, "GPS/SINK" );
   













      //mspp_logger logger( "file:///opt/mspp/config/logger.json" );
      mspp_logger logger( configuration.logger_config_file() );
      logger.start_service( );

      //mspp_manager manager( "file:///opt/mspp/config/manager.json", logger );
      mspp_manager manager( configuration.manager_config_file(), logger );
      manager.start_services();

      // This detaches the manager service and will immediately exit()
      manager.detach();
   } 
   catch ( const mspp::mspp_startup_exception &e ) 
   {
      // Run in "limp home" mode -- helpful for debugging, 
      // remote assistance, operator-assisted recovery, etc.
      mspp::mspp_manager failsafe_manager( configuration.manager_config_file(), e.what() );
     
      failsafe_manager.start_services();
      // This detaches the manager service and will immediately exit()
      failsafe_manager.detach();
   } 
   catch ( const std::runtime_error &e ) 
   {
      
   } 
   catch ( const std::logic_error &e ) 
   {

   }

   return 0; 
}
