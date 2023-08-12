//
//  C++ standard headers
//
#include <algorithm>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <sstream>

//
//  C standard headers
//
#include <stdexcept>
#include <termios.h>

//
// 3rd party headers
//

//
//  TM proprietary headers
//
#include <Serial.hpp>
#include <mspp_exceptions.hpp>

namespace mspp 
{
   bool Serial::open( )
   { 
      if ( m_fd < 0 )
      {
         return false;  
      }

      
  
      // NOTE: The most common problem is "Permission denied" on the
      //       port. An easy fix -- run the following command:
      //      
      //   $ sudo adduser $USER dialout
      //
      m_fd = ::open( m_port_name.c_str(), O_RDWR );
      if ( m_fd < 0 )
      {
         std::stringstream err_msg;
         err_msg << __FILE__  
                 << ":"  
                 << __FUNCTION__  
                 << ": UART port ("
                 << m_port_name
                 << "): error("
                 << strerror(errno)
                 << ")";
         throw std::runtime_error( err_msg.str() );
      }
      return true;
   }

   void Serial::close( )
   {
      if ( m_fd < 0 )
      {
         return;
      }
      flush( );
      ::close( m_fd );
      m_fd = -1;
   }

   int Serial::read( uint8_t *data, size_t len ) const
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      if ( data == nullptr )
      {
         return -1;  
      }
      if ( ( len == 0 ) || ( len > 4096 ) )
      {
         return -1;
      }
      int retval{0};

      retval = ::read( m_fd, data, len );
      return retval;
   }

   int Serial::read( std::vector<uint8_t> &read_str ) const
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      int retval{0};
      uint8_t c;

      while (1) 
      {
         // I'm counting on this call to read() to be a blocking
         // call with a short timeout interval. Otherwise, this
         // is a broken solution...
         retval = ::read( m_fd, &c, 1 );
         if ( retval == 1 )
         {
            read_str.push_back( c );
         }
         else 
         {
            break;
         }
      } 
      return retval;
   }

   int Serial::write( const uint8_t *data, std::size_t len) const
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      if ( data == nullptr ) 
      {
         return -1;
      }
      if ( ( len == 0 ) || ( len > 4096 ) )
      {
         return -1;
      }
      int retval = 0;

      retval = ::write( m_fd, data, len );
      flush( );
      return retval;
   }
   
   int Serial::write( const std::vector<uint8_t> &write_str )  const
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      int retval{0};

      retval = 
      ::write( m_fd, static_cast<const uint8_t *>( write_str.data() ), write_str.size( ) );
      return retval;
   }

   void Serial::flush( ) const
   {
      if ( m_fd < 0 )
      {
         return;  
      }
      tcdrain( m_fd );
   }
}
