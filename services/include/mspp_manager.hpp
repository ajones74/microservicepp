#ifndef _MSPP_MANAGER_HPP_
#define _MSPP_MANAGER_HPP_

#include <string>
#include <mspp_base_element.hpp>
#include <mspp_logger.hpp>

namespace mspp {
   class mspp_manager : public mspp_base_element {
      public:
         // NO default constructors.
         mspp_manager( ) = delete;
         explicit mspp_manager( const std::string &src_uri, 
                                mspp_logger &logger );

         virtual ~mspp_manager( );

         bool start_service ( mspp_base &service );
         bool start_services( );

         bool stop_service( mspp_base &service );
         bool stop_services( );

         void detach( );
   };
}

#endif // _MSPP_MANAGER_HPP_
