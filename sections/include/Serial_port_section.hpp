#ifndef _SERIAL_PORT_SECTION_HPP_
#define _SERIAL_PORT_SECTION_HPP_ 

#include <string>
#include <thread>

#include <Section.hpp>
#include <Serial.hpp>

#include <nng/nng.h>
#include <nng/protocol/pipeline0/pull.h>
#include <nng/protocol/pipeline0/push.h>


namespace mspp {
   class Serial_port_section : public Section 
   {
      public:
         Serial_port_section( const std::string &init_string ) :
            Section{ init_string }, 
            m_serial{ std::make_unique<Serial>( init_string ) }
         { }
         virtual void connect( );
         virtual void start( );
         virtual void stop( );

      private:
         nng_socket m_nng_socket;
         Logging m_log;
         std::unique_ptr<Serial> m_serial;

         bool open_serial_port( );
         bool open_nng_sockets( );
         void close_serial_port( );
         void close_nng_sockets( );
         void processing_loop( );
   };
}

#endif // _SERIAL_PORT_SECTION_HPP_
