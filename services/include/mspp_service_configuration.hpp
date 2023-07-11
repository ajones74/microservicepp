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

            std::string logger_config_file( );
            std::string manager_config_file( );
    };
}

#endif // _MSPP_CONFIGURATION_HPP_
