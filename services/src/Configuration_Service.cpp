#include <iostream>
#include <vector>
#include <string>

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

   const std::string our_service_name{"Configuration Service" };

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

     
      Pipeline *configuration_service_pipe = 
         new Configuration_service_server_pipe{ our_service_name };

      configuration_service_pipe->bind( );

      // Create our local Configuration service...
      Service &configuration_service = new Service( our_service_name );
      // Add the pipeline(s) to the service
      configuration_service.add( configuration_service_pipe );

      // This calls the .start() methods for all associated pipes.
      configuration_service->start( );

      // This function never returns unless SIGKILL/SIGTERM/SIGABRT recv'd      
      configuration_service->run( );
 
#if 0
      // Data source -- listen for requests
      Section *configuration_service_source_section = 
            new Configuration_service_source_section;
  
      // No data filters -- if there were any, they'd go here...
      
      // No data formatters -- if there were any, they'd go here...

      // Data sink
      Section *req_rep_processor = new Configuration_service_processor_section;

      // Create a data processing pipeline specific to our service.
      Pipeline &configuration_service_pipe = new Service_source_pipe{ our_service_name };
      configuration_service_pipe.add_source( configuration_service_source_section );
      configuration_service_pipe.add_source( logging_service_source_section );

#endif

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
