//
//  C++-17 header files
//
#include <iostream>
#include <vector>
#include <string>
#include <variant>
//
// 3rd-party header files
//
#include <nlohmann/json.hpp>
//
//  Tampa Microwave proprietary header files.
//
#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>
#include <Service.hpp>
#include <Section.hpp>
#include <GPS_service.hpp>
#include <Logging_service_pipelines.hpp>
#include <Configuration_service_pipelines.hpp>
#include <GPS_service_pipelines.hpp>

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

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      const std::string our_service_name{"GPS Service" };
      
      //
      //  Create a pipeline to the logging service
      //
      std::unique_ptr< Pipeline > logging_service_pipe = 
         std::make_unique< Logging_service_client_pipe>( our_service_name );
      // Throws an exception on failure to connect.
      logging_service_pipe->connect();

      //
      //  Create a pipeline to the configruation service
      //
      std::unique_ptr< Pipeline > configuration_service_pipe = 
         std::make_unique< Configuration_service_client_pipe >( our_service_name );
      // Throws an exception on failure to connect.
      configuration_service_pipe->connect();
      // Pull a copy of the system-wide configuration from the 
      // configuration service as a JSON-structured document.
      json config_json = configuration_service_pipe->pull( "format=JSON" );

      //
      //  Create our own, service-specific pipeline
      //
      std::unique_ptr< Pipeline > our_data_pipe = 
         std::make_unique< GPS_service_data_pipe >( our_service_name );
      // Throws an exception on failure to connect.
      our_data_pipe->connect();

      //
      //  Create our local GPS service
      //
      std::unique_ptr< Service > GPS_service = 
         std::make_unique< GPS_Service >( our_service_name );

      // Add logging pipe, configuration pipe, and data-pipe to the service.
      GPS_service->add( std::move( logging_service_pipe ) );
      GPS_service->add( std::move( configuration_service_pipe ) );
      GPS_service->add( std::move( our_data_pipe ) );

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