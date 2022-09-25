#include <iostream>

#include <mspp_exceptions.hpp>

namespace mspp {
const char *mspp_startup_exception::what ( ) const noexcept override
{
   return "Manager startup/configuration error";
}

}
