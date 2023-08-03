#include <iostream>

#include <cstring>   // for memset()
#include <unistd.h>  // for read(), write

#include <mspp_exceptions.hpp>
#include <Serial_port_section.hpp>

namespace mspp {

   // This is called in-directly -- called via the owning 
   // pipeline and via its own "connect()" method.
   void Serial_port_section::connect( )
   {
      if ( true == m_connected.load() )
      {
         // Already connected -- don't wan't to allocate resource 
         // multiple times!
         return;
      }
      if ( false == open_serial_port( ) ) 
      {
         // error
         return; 
      }
      if ( false == open_nng_sockets( ) )
      {
         // error
         return; 
      }
     m_connected.store( true );
   }

   void Serial_port_section::start( )
   {
      if ( false == m_connected.load( ) )
      {
         // We are here most likely because:
         //  A) "connect()" is failing/failed.
         //  B) "stop()" was called just prior to this call, and this is an
         //     attempt to restart...
         throw mspp_startup_exception( "start() invoked before connect()" );
      }
      m_thread = std::thread( &Serial_port_section::processing_loop, this );
   }

   void Serial_port_section::stop( )
   {
      if ( false  == m_connected.load( ) )
      {
         // already disconnected.
         return;
      }
      m_started.store( false );
      if (m_thread.joinable( ) ) 
      {
         m_thread.join( );
      }
   }

   bool Serial_port_section::open_serial_port( )
   {
      bool passed = false;

      return passed;
   }
 
   bool Serial_port_section::open_nng_sockets( )
   {
      bool passed = false;

      return passed;
   }

   void Serial_port_section::close_serial_port( )
   {

   }
 
   void Serial_port_section::close_nng_sockets( )
   {

   }

   void Serial_port_section::processing_loop( )
   {
      const uint8_t buff_size{ 128 };
      uint8_t buff[buff_size];
      uint8_t read_count;

      using namespace std::chrono_literals;  

      m_started.store( true );
      while ( true == m_started.load( ) )
      {
         memset( buff, 0, buff_size );
         read_count = read( m_port_fd, buff, buff_size );
         if ( read_count < 0 ) 
         {
            // what to do??? for now, simply sleep a bit and retry...
            std::this_thread::sleep_for(10ms);
            continue;
         }
         if ( read_count == 0 )
         {
            // simply retry?
            continue;
         }

         

      }
      close_serial_port( );
      close_nng_sockets( );
      m_connected.store( false );
   }
}
