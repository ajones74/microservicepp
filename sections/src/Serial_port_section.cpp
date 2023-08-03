#include <iostream>

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
      m_started.store( true );
      while ( true == m_started.load( ) )
      {

      }
      // a) Shutdown the serial port...
      // b) Shutdown the NNG sockets...
      
      m_connected.store( false );
   }



}
