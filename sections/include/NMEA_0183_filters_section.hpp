#ifndef _NMEA_0183_FILTERS_HPP_
#define _NMEA_0183_FILTERS_HPP_ 

#include <Section.hpp>

namespace mspp {
   class NMEA_0183_Framer_section : public Section {
      public:
         NMEA_0183_Framer_section( const std::string &init_string ) :
            Section{ init_string }
         { }

         virtual void connect( );

         virtual void start( );

         virtual void stop( );

      private:

   };
}

#endif // _NMEA_0183_FILTERS_HPP_ 
