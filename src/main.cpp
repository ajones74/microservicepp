#include <iostream>
#include <mspp_configuration.hpp>
#include <mspp_exceptions.hpp>
#include <mspp_logger.hpp>
#include <mspp_manager.hpp>


int main(int argc, const char **argv) 
{
   try 
   {
      using namespace mspp;

      mspp_configuration configuration( argc, argv );
      configuration.start_service( );
     
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
      mspp::mspp_manager failsafe_manager;
      
      // This detaches the manager service and will immediately exit()
      failsafe_manager.run( e.what() );
   } 
   catch ( const std::runtime_error &e ) 
   {
      
   } 
   catch ( const std::logic_error &e ) 
   {

   }

   return 0; 
}
