#ifndef _MSPP_MANAGER_HPP_
#define _MSPP_MANAGER_HPP_

#include <string>
#include <mspp_base_service.hpp>
#include <mspp_service_logger.hpp>

namespace mspp {
   class mspp_manager : public mspp_base_service {
      public:
         // NO default constructors.
         mspp_manager( ) = delete;

         explicit mspp_manager( const std::string &src_uri, 
                                mspp_logger &logger );

         explicit mspp_manager( const std::string &src_uri, 
                                const std::string &exception_msg );
         virtual ~mspp_manager( );

         bool start_service( ) override;
         bool start_service ( mspp_base_service &service );
         bool start_services( );

         bool stop_service( ) override;
         bool stop_service( mspp_base_service &service );
         bool stop_services( );

         void detach( );
   };
}

#endif // _MSPP_MANAGER_HPP_
