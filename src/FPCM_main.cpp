#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include <mspp_exceptions.hpp>

#include <Pipeline.hpp>
#include <Custom_pipelines.hpp>

#include <Service.hpp>
#include <FPCM_Service.hpp>


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

   const std::string our_service_name{"FPCM Service" };

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      Pipeline *logging_service_pipe = 
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


      Pipeline *discovery_service_pipe = 
         new Discovery_service_server_pipe;
      // Throws an exception on failure to bind.
      discovery_service_pipe->bind( );

      //
      // Create our local FPCM service...Use a class derived from Service,
      // as we have to implement the "run()" method -- by default,
      // the "run()" method in most services simply responds to service 
      // discovery polling.
      Service &service = new FPCM_Service( our_service_name );

      // Add Logging pipe, configuration pipe, and the data-pipe to the service.
      service.add( logging_service_pipe );
      service.add( configuration_service_pipe );
      service.add( discovery_service_pipe );

      // This calls the .start() methods (if applicable) for all 
      // associated pipes.
      service->start( );

      // This function never returns unless SIGKILL/SIGTERM/SIGABRT recv'd      
      service->run( run );
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
