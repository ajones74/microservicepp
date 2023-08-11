#include <iostream>

#include <termios.h>

#include <Serial.hpp>

namespace mspp 
{
   bool Serial::open( )
   { 
      if ( m_fd < 0 )
      {
         return false;  
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

   int Serial::read( char *data, size_t len )
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      int retval{0};

      retval = ::read( m_fd, data, len );
      return retval;
   }

   int Serial::read( const std::string read_str )
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      int retval{0};

      return retval;
   }

   int Serial::write( const char *data, std::size_t len)
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      int retval = 0;

      retval = ::write( m_fd, data, len );
      flush( );
      return retval;
   }
   
   int Serial::write( const std::string read_str )
   {
      if ( m_fd < 0 )
      {
         return -1;  
      }
      int retval{0};

      retval = write( read_str.c_str(), read_str.length( ) );
      return retval;
   }

   void Serial::flush( )
   {
      if ( m_fd < 0 )
      {
         return;  
      }
      tcdrain( m_fd );
   }
}
