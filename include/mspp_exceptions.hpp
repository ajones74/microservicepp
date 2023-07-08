#ifndef _MSPP_EXCEPTIONS_HPP_
#define _MSPP_EXCEPTIONS_HPP_

#include <string>
#include <exception>

/* Almost all runtime exceptions should be handled using std::runtime_error
 * objects.
 *
 * Almost all logic exceptions should be handled using std:logic_error objects
 */ 

namespace mspp {

/* When this exception is thrown, the calling code should revert to
 * a default configuration, or some other "fail safe" mode and
 * subsequently log or otherwise notify the operator (via a modal dialog
 * box, or via NNG networked message, for example).
 */
class mspp_startup_exception : public std::runtime_error {
   public:
      explicit mspp_startup_exception( const std::string &what_msg );
};



}


#endif // _MSPP_EXCEPTIONS_HPP_
