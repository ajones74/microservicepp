#ifndef _SERIAL_PORT_SECTION_HPP_
#define _SERIAL_PORT_SECTION_HPP_ 

#include <Section.hpp>

namespace mspp {
   class Serial_port_section : public Section 
   {
      public:
         Serial_port_section( const std::string &init_string ) :
            Section{ init_string }, 
            m_port_fd{ -1 }
         { }
         virtual void connect( );
         virtual void start( );
         virtual void stop( );

      private:
         int m_port_fd;
     
         bool open_serial_port( );
         bool open_nng_sockets( );

   };
}

#endif // _SERIAL_PORT_SECTION_HPP_
