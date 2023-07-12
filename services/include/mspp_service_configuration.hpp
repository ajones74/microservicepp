#ifndef _MSPP_CONFIGURATION_HPP_
#define _MSPP_CONFIGURATION_HPP_

#include <string>

#include <mspp_base_service.hpp>

namespace mspp {

    class mspp_configuration : public mspp_base_service {
        public:
            // NO default ctor
            mspp_configuration( ) = delete;

            mspp_configuration( int argc, const char **argv );

            ~mspp_configuration( );

            virtual bool start_service( );
            virtual bool stop_service( );

            std::string logger_config_file( ) const;
            std::string manager_config_file( ) const;
         private:
            // The absolute path and filename of the JSON-formatted
            // configuration file for the entire MSPP microservices framework.
            std::string m_config_filename;
            // The JSON-formatted 
            std::
            // Valid URIS:
            // * "service:mspp:config:file:///opt/mspp/config/config.json"
            // * "service:mspp:config:odbc:Database=/opt/mspp/database/config.db;.."
            // * "service:mspp:config:https://localhost:5150/config?user=joe&pass=password"  
            // * "service:mspp:config:udp://localhost:5151/config
            // 
            bool provided_config( const char *config_filename);
            bool default_config( ); 
            bool parse_config_file( );
    };
}

#endif // _MSPP_CONFIGURATION_HPP_
