#include <iostream>
#include <mspp_exceptions.hpp>

namespace mspp {

mspp_startup_exception::mspp_startup_exception( const std::string &what_msg )
   : std::runtime_error( what_msg ) 
{
}
   
}
