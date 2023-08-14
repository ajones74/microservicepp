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
   // TODO:  Configuration parameters for this port need
   // to be fetched from an external service, or a JSON-formatted
   // local config file, or a sqlite database, or etcetera.
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
 
      // To restore the port settings when/if this
      // port is closed  
      if ( tcgetattr(m_fd, &m_prior_tty) != 0)
      {
         return false;
      }
     
      if ( tcgetattr(m_fd, &m_session_tty) != 0)
      {
         return false;
      }
      
      // 1 stop-bit -- most common
      m_session_tty.c_cflag &= ~CSTOPB;
      // 2 stop-bits -- rare.
      //m_session_tty.c_cflag |= CSTOPB;

      // NO parity
      m_session_tty.c_cflag &= ~PARENB;
      // ENABLE parity -- almost never the case...
      //m_session_tty.c_cflag |= PARENB;  

      // CLEAR all of the size bit-fields, then explicitly
      // set only one:
      m_session_tty.c_cflag &= CSIZE;
      // 8 data-bits per byte -- almost always...
      m_session_tty.c_cflag |= CS8;
   
      // Disable RTS/CTS hardware flow control (most common)
      m_session_tty.c_cflag  &= ~CRTSCTS;
      // Enable RTS/CTS hardware flow control (un-common)
      //m_session_tty.c_cflag &= CRTSCTS; 
     
      // Setting CLOCAL disables modem-specific signals like DCD, DTR.
      // It also disables the SIGHUP signal for any disconnects. Good!
      // Setting CREAD is obvious -- READ data....!
      m_session_tty.c_cflag |= CLOCAL; 
      m_session_tty.c_cflag |= CREAD; 

      // Disable Canonical (newline-termination-sensitive) mode --
      m_session_tty.c_cflag &= ~ICANON;

      // I'm not sure that echo is enabled when in CANONical mode --
      // disable echo, just in case!
      m_session_tty.c_cflag &= ~ECHO;    // Disable ECHO
      m_session_tty.c_cflag &= ~ECHOE;   // Disable ECHO ERASE
      m_session_tty.c_cflag &= ~ECHONL;  // Disable ECHO NEW LINE.

      // Disable the interpretation of INTR (Ctrl-C), QUIT (Ctrl-\),
      // and SUSP (Ctrl-Z)  signals.
      m_session_tty.c_cflag &=~ISIG; 

      // Disable SOFTWARE flow-control: IXOFF, IXON, IXANY, etc.
      m_session_tty.c_iflag &= ~(IXON | IXOFF | IXANY ); 
      
      // Disable the processing/interpretation of received data bytes:
      m_session_tty.c_iflag &= ~( IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL ); 

      // Disable the processing/interpretation of outgoing data bytes:
      m_session_tty.c_oflag &= ~OPOST;    // No processing/interpretation of output bytes.
      m_session_tty.c_iflag &= ~ONLCR;    // No conversion of NL or CR or NL/CR, etc.

      //Setup read time-out timers...Kind of tricky...
      m_session_tty.c_cc[VMIN]  = 0;  // Set VMIN to a value greater than zero for indefinite timeout.
      m_session_tty.c_cc[VTIME] = 1;  // 1 deci-second, or 10 millisecond timeout.
      
      // Set the baud-rate...
      cfsetspeed(&m_session_tty, B9600);   // TODO: This is BAD -- hardcoding the baud-rate!
    
      // Apply the changes...
      if ( tcsetattr(m_fd, TCSANOW, &m_prior_tty ) != 0 )
      {  
         // Not really worth throwing an exception, for, is it?
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
      // Restore the port settings as they were before
      // this application code was called
      tcsetattr(m_fd, TCSANOW, &m_prior_tty);
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
