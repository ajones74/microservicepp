#include <cstddef>
#include <iostream>

#include <mspp_service_configuration.hpp>
#include <mspp_exceptions.hpp>


namespace mspp {
   

   mspp_configuration::mspp_configuration( int argc, const char **argv )
   {
      if ( argc == 1 )
      {
         // Too few arguments provided. Simply bail.
         throw mspp_startup_exception( "Invalid invocation -- too few command-line options." );
      }
      else if ( argc == 2 )
      {
         set_config_filename( argv[1] );
      }
      else
      {
         // Too many arguments provided. Simply bail. This could be a hack attempt.
         throw mspp_startup_exception( "Invalid invocation -- too many command-line options." );
      }
      parse_config_file( );
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

   void mspp_configuration::set_config_filename( const char *config_filename = nullptr )
   {
      if ( config_filename == nullptr )
      {
         throw mspp_startup_exception( "Invalid invocation." );
      }
      m_config_filename = std::string{ config_filename };
      return true;
   }

    // THIS: "service:mspp:configuration:source:JSON:file://./mspp_config.json" 
    // OR:   "service:mspp:configuration:source:JSON:file://<CUSTOM-PATH-FILENAME>" 
   void mspp_configuration::parse_config_file( )
   {
      mspp_base_pad &file = new mspp_pad_file{ m_config_filename };
      mspp_base_element &json = new mspp_element_framer_JSON{ file };

      this.add_source( json );

      // define "m_config_json" to whatever JSON library we are going to use...
      m_config_json = source.json.file.read_all( );
      return true;
   }
}
