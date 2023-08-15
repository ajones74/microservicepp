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
      return m_serial->open( );
   }
 
   bool Serial_port_section::open_nng_sockets( )
   {
      int retval{0};

      // listen and push
      if( ( retval = nng_push0_open( &m_nng_socket ) ) != 0)
      {
         // throw an exception here???
         return false;
      }
      if ( ( retval = nng_listen( m_nng_socket, "ipc string", NULL, 0) ) != 0 )
      {
         // throw an exception here???
         return false;
      }
      return true;
   }

   void Serial_port_section::close_serial_port( )
   {
      m_serial->close( );
   }
 
   void Serial_port_section::close_nng_sockets( )
   {
      // TODO: Is this the best test to ensure the socket is
      //       valid (or open) before closing it?
      if ( nng_socket_id( m_nng_socket ) > 0 )
      {
         nng_close( m_nng_socket );
      }
   }

   void Serial_port_section::processing_loop( )
   {
      ssize_t read_count;
      int write_count;
      
      const size_t buff_size{256};
      std::vector<uint8_t> buff(buff_size, 0);

      using namespace std::chrono_literals;  

      m_started.store( true );
      while ( true == m_started.load( ) )
      {
         buff.clear();
         read_count = m_serial->read( buff );
         if ( read_count < 0 ) 
         {
            // what to do??? for now, simply log the issue
            // and sleep a bit and retry...
#if 0
            m_log.warn << __FILE__ 
                       << __FUNCTION 
                       << " Serial port("
                       << m_port_name 
                       << ") is closed?  Errono("
                       << errno 
                       << ")";
#endif 
            std::this_thread::sleep_for(10ms);
            continue;
         }
         if ( read_count == 0 )
         {
            // Not an error, but there is nothing in the port
            // read queue. Simply retry after we give up our 
            // slot in the scheduler.
            std::this_thread::yield();
            continue;
         }

         write_count = nng_send( m_nng_socket, buff.data(), read_count, 0 );
         if (write_count != 0 )
         {
#if 0
            m_log.warn << __FILE__,
                       << __FUNCTION__,
                       << " Error on writing data on socket("
                       << write_count 
                       << ")";
#endif 
         }
      }
      close_serial_port( );
      close_nng_sockets( );
      m_connected.store( false );
   }
}
