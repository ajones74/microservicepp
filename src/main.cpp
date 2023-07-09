#include <iostream>
#include <mspp_exceptions.hpp>
#include <mspp_manager.hpp>


int main(int argc, char **argv) 
{
   try 
   {
      using namespace mspp;
     
      mspp_logger logger( "file:///opt/mspp/config/logger.json" );
      logger.start_service( );

      mspp_manager manager( "file:///opt/mspp/config/manager.json", logger );
      manager.start_services();

      // This detaches the manager service and will immediately exit()
      manager.run();
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
