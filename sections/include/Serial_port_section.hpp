#ifndef _SERIAL_PORT_SECTION_HPP_
#define _SERIAL_PORT_SECTION_HPP_ 

#include <Section.hpp>

namespace mspp {

   class Serial_port_section : public Section 
   {
      public:
         Serial_port_section( const std::string &init_string ) :
            Section{ init_string }
         { }

         virtual void start( );
         virtual void stop( );

      private:

   };
}

#endif // _SERIAL_PORT_SECTION_HPP_
