#include <iostream>

#include <mspp_configuration.hpp>

namespace mspp {

    mspp_configuration::mspp_configuration( int argc, const char **argv )
    {

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
