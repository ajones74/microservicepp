#ifndef _MSPP_MANAGER_HPP_
#define _MSPP_MANAGER_HPP_

#include <string>

enum class MSPP {
   ALL,
   CONFIGURATION,
   LOGGING,
   APP_SERVICES,
   INVALID 
};

namespace mspp {

class mspp_manager {
   public:
      mspp_manager( );
      ~mspp_manager( );
      void manage_signals( );
      void configuration_source( const std::string &source_filename );
      void start_service ( const int service_type );
      void start_services ( ); 
      void run ( );

   private:

};

}

#endif // _MSPP_MANAGER_HPP_
