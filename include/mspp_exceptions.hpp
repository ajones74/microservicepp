#ifndef _MSPP_EXCEPTIONS_HPP_
#define _MSPP_EXCEPTIONS_HPP_

#include <exception>

namespace mspp {

class mspp_startup_exception : public std::exception {
   const char *what ( );
};

}


#endif // _MSPP_EXCEPTIONS_HPP_
