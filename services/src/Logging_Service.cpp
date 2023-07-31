#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>
#include <Service.hpp>


int main(int argc, const char **argv) 
{
   int exit_value = EXIT_SUCCESS;

   const std::string our_service_name{"Logging Service" };

   try 
   {
      using namespace mspp;
      using json = nlohmann::json;

      // Data source -- listen and pull
      Section *logging_service_source_section = 
            new Logging_service_source_section;
  
      // No data filters -- if there were any, they'd go here...
      
      // No data formatters -- if there were any, they'd go here...

      // Data sink -- always log to syslogd, or whatever systemd uses...
      Section *logging_to_syslogd_section = new Logging_to_syslogd_section;
      // Data sink -- conditionally log to file.
      // Default logfile is APPENDED to /tmp/fpcm_logging.txt
      Section *logging_to_file_section = new Logging_to_file_section; 

      // Create a logging data pipeline specific to our service.
      Pipeline &systemd_pipe = new Service_source_pipe{ our_service_name + " - syslogd" };
      systemd_pipe.add_source( logging_service_source_section );
      systemd_pipe.add_sink( logging_to_syslogd_section );

      // Create a logging data pipeline specific to our service.
      Pipeline &file_pipe = new Service_source_pipe{ our_service_name + " - file" };
      file_pipe.add_source( logging_service_source_section );
      file_pipe.add_sink( logging_to_file_section );

      // Create our local Logging service...
      Service &logging_service = new Service( our_service_name );
      // Add the two pipelines to the service
      logging_service.add( systemd_pipe );
      logging_service.add( file_pipe );

      // This calls the .start() methods for all associated pipes.
      logging_service->start( );

      // This function never returns unless SIGKILL/SIGTERM/SIGABRT recv'd      
      logging_service->run( );
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
