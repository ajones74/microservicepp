#include <iostream>
#include <mspp_manager.hpp>
#include <mspp_exception.hpp>


int main(int argc, char **argv) 
{
   try {
      mspp::mspp_manager;

      manager.manage_signals();

      manager.configuration_source("config.json");

      manager.start_service( MSPP::CONFIGURATION );
      manager.start_service( MSPP::LOGGING );

      manager.start_services();

      // This is a blocking call -- will not (normally) return
      manager.run();
   } catch ( const mspp::mspp_exception &e ) {

   } catch ( const std::runtime_error &e ) {

   }
   return 0; 
}
