#include <iostream>

#include <mspp_service_manager.hpp>
#include <mspp_exceptions.hpp>

namespace mspp {
    mspp_manager::mspp_manager( const std::string &src_uri,
                                mspp_logger &logger )
    {
       
    }

    mspp_manager::mspp_manager( const std::string &src_uri,
                                const std::string &exception_msg )
    {

    }

    mspp_manager::~mspp_manager( )
    {
       
    }

    bool mspp_manager::start_service( )
    {
        return true;
    }

    bool mspp_manager::start_service( mspp_base_service &service  )
    {
       return true;
    }

    bool mspp_manager::start_services( )
    {
       return true;
    }

    bool mspp_manager::stop_service( )
    {
        return true;
    }

    bool mspp_manager::stop_service( mspp_base_service &service )
    {
       return true;
    }

    bool mspp_manager::stop_services( )
    {
       return true;
    }

    void mspp_manager::detach( )
    {

    }
}


