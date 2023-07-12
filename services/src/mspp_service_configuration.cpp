#include <iostream>

#include <mspp_service_configuration.hpp>
#include <mspp_exceptions.hpp>


namespace mspp {
   

   mspp_configuration::mspp_configuration( int argc, const char **argv )
   {
      if ( argc == 1 )
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

    std::string mspp_configuration::logger_config_file( ) const 
    {
        return std::string{""};
    }

   std::string mspp_configuration::manager_config_file( ) const
   {
      return std::string{""};
   }

   bool mspp_configuration::provided_config( const char *config_filename )
   {
      if ( not config_filename )
      {
         throw mspp_startup_exception( "NULL filename for configuration" );
      }
      m_config_filename = std::string{ config_filename };
      return parse_config_file();
   }

   // Use a default config file, "./mspp_config.json"
   bool mspp_configuration::default_config( )
   {
      m_config_filename = std::string{"./mspp_config.json"};
      return parse_config_file();
   }

    // THIS: "service:mspp:configuration:source:JSON:file://./mspp_config.json" 
    // OR:   "service:mspp:configuration:source:JSON:file://<CUSTOM-PATH-FILENAME>" 
   bool mspp_configuration::parse_config_file( )
   {
      mspp_base_pad &file = new mspp_pad_file{ m_config_filename };
      mspp_base_element &json = new mspp_element_framer_JSON{ file };

      this.add_source( json );

      // define "m_config_json" to whatever JSON library we are going to use...
      m_config_json = source.json.file.read_all( );
      return true;
   }
}
