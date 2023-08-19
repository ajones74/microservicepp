//
//  C++-17 header files
//
#include <iostream>
#include <memory>
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

// Agents 
#include <Logging.hpp>
#include <Configuration.hpp>

// services
#include <GPS.hpp>

#include <Pipeline.hpp>
#include <Service.hpp>
#include <Section.hpp>
#include <GPS_service_pipelines.hpp>

#include <FPCM_version.h>

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
int main( int argc, const char **argv )
{
   int exit_value = EXIT_SUCCESS;

   try {
      using namespace mspp;
      using json = nlohmann::json;

      // The timestamp and IP address of this service will be appended
      // to this greeting/banner, later.
      pid_t our_pid = getpid( );
      std::stringstream greeting;
      greeting << "HELLO from pid("
               << static_cast<int>( our_pid )
               << "), GPS service build details: ("
               << git_build_details
               << "), TIME: ("
               << __TIME__
               << "), DATE: ("
               << __DATE__ << ")";

      std::string pid_string{ std::to_string( our_pid ) };

      //
      // Create our logging Agent -- it connects to the logging service
      //
      Logging *log = Logging::instance();
      log->connect( );
      log->info( greeting.str() );

      //
      // Create our configuration Agent -- it connects to the Configuration service
      //
      Configuration *config = Configuration::instance();
      config->connect( );
      json config_json = config->pull( "format=JSON" );


      //gps->bind( "ipc:///tmp/GPS_data.ipc" );


      //  The stuff I implement below will eventually get migrated into a Dispatcher object:
      //  * It will instantiate its own Logging instance
      //  * It will instantiate its own Configuration instance
      //  * It will invoke the "start()" and "stop()" messages of the Service instance (in this case, the "GPS" service)
      //  * It will send a periodic status message to the Logging server via our Logging Agent.
      //  * It will listen for incoming messages on "ipc:///tmp/GPS_mgmt.ipc" file:
      //  ** incoming message can "stop()" the event loop
      //  ** incoming message can force another "pull()" from the configuration agent.
      //  ** incoming message can force the instantiaton of another Agent and add it to the event loop.
      //
      //
      // std::unique_ptr< Dispatcher > dispatcher = std::make_unique< Dispatcher >( );

      // Questions / Considerations for the dispatcher:
      // *
      //   dispatcher->dispatch( )


      ///////////////////////////////////////////////////////////////////







#if 0
      //
      //  Create our own, service-specific pipeline
      //
      std::unique_ptr< Pipeline > our_data_pipe =
         std::make_unique< GPS_service_data_pipe >(  pid_string );
      our_data_pipe->connect();

      //
      //  Create our local GPS service
      //
      std::unique_ptr< Service > GPS_service =
         std::make_unique< GPS_Service >( pid_string );

      // Add logging pipe, configuration pipe, and data-pipe to the service.
//      GPS_service->add( std::move( logging_service_pipe ) );
//      GPS_service->add( std::move( configuration_service_pipe ) );
      GPS_service->add( std::move( our_data_pipe ) );

      // This calls the .start() methods (if applicable) for all
      // associated pipes.
      GPS_service->start( );

      // This function never returns unless SIGKILL/SIGTERM/SIGABRT recv'd
      GPS_service->run( );
#endif

   } catch ( const mspp::mspp_startup_exception &e ) {
      std::cout << "STARTUP ERROR(" << e.what() << ")" << std::endl;
      exit_value = EXIT_FAILURE;
   } catch ( const std::runtime_error &e ) {
      std::cout << "RUNTIME ERROR(" << e.what() << ")" << std::endl;
      exit_value = EXIT_FAILURE;
   } catch ( const std::logic_error &e ) {
      std::cout << "LOGIC ERROR(" << e.what() << ")" << std::endl;
      exit_value = EXIT_FAILURE;
   } catch ( ... ) {
      std::cout << "UNHANDLED ERROR(" <<  ")" << std::endl;
      exit_value = EXIT_FAILURE;
   }
   std::cout << "EXITING" << std::endl;
   return exit_value;
}
