#include <iostream>

#include <mspp_service_configuration.hpp>

namespace mspp {
   

   mspp_configuration::mspp_configuration( int argc, const char **argv )
   {
      if ( argc < 2 )
      {
         // No path to a config-file provided. Go with a default in the CWD:
         if ( not default_config( ) )
         {
            throw mspp_startup_exception( "Invalid invocation -- too few command-line options." );
         }
      }
      else if ( argc == 2 )
      {
         if ( not provided_config( argv[1] ) )
         {
            throw mspp_startup_exception( "Invalid invocation -- invalid command-line options." );
         }
      }
      else
      {
         // Too many arguments provided. Simply bail. This could be a hack attempt.
         throw mspp_startup_exception( "Invalid invocation -- too many command-line options." );
      }
   }

   mspp_configuration::~mspp_configuration( ) 
   {

   }

   bool mspp_configuration::start_service( )
   {
      return true;
   }

   bool mspp_configuration::stop_service( )
   {
      return true;
   }

    std::string mspp_configuration::logger_config_file( )
    {
        return std::string{""};
    }

    std::string mspp_configuration::manager_config_file( )
    {
        return std::string{""};
    }
}
