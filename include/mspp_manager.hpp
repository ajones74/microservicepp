#ifndef _MSPP_MANAGER_HPP_
#define _MSPP_MANAGER_HPP_

#include <string>

namespace mspp {

enum class service_type {
   ALL,
   CONFIGURATION,
   LOGGING,
   APP_SERVICE,
   INVALID 
};


class mspp_manager {
   public:
      mspp_manager( );
      ~mspp_manager( );
      void manage_signals( );
      void configuration_source( const std::string &source_filename );
      void start_service ( const service_type type );
      void start_services ( ); 
      void run ( );

   private:

};

}

#endif // _MSPP_MANAGER_HPP_
