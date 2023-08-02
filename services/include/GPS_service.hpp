#ifndef _GPS_SERVICE_HPP_
#define _GPS_SERVICE_HPP_ 

#include <Service.hpp>

namespace mspp {

   class GPS_Service : public Service 
   {
      public:
         GPS_Service( const std::string &service_name ) :
            Service{ service_name }
         { }

         virtual void start( );
         virtual void run( );

      private:
   };

}

#endif   // _GPS_SERVICE_HPP_ 
