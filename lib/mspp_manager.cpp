#include <iostream>

#include <mspp_base.hpp>
#include <mspp_manager.hpp>
#include <mspp_exceptions.hpp>

namespace mspp {
    mspp_manager::mspp_manager( const std::string &src_uri,
                                mspp_logger &logger )
    {
       
    }

    mspp_manager::~mspp_manager( )
    {
       
    }

    bool mspp_manager::start_service( mspp_base &service  )
    {
       return true;
    }

    bool mspp_manager::start_services( )
    {
       return true;
    }

    bool mspp_manager::stop_service( mspp_base &service )
    {
       return true;
    }

    bool mspp_manager::stop_services( )
    {
       return true;
    }

    bool mspp_manager::run ( )
    {
        return true;
    }
}


