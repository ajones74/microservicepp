#ifndef _SERIAL_HPP_
#define _SERIAL_HPP_

#include <iostream>
#include <vector>
#include <cstddef>

#include <termios.h>
#include <unistd.h>

namespace mspp {

   class Serial {
      public: 
         Serial() = delete;
         Serial( const std::string &port_name ) :
            m_fd{-1},
            m_port_name{port_name} 
         { }
         ~Serial( );

         bool open( );
         void close( );
         
         int read(  uint8_t *data, size_t len ) const;
         int read(  std::vector<uint8_t> &read_str ) const;
         
         int write( const uint8_t*data, size_t len ) const;
         int write( const std::vector<uint8_t> &write_str ) const;
  
      protected:
      private:
         int m_fd;
         std::string m_port_name;
         struct termios m_prior_tty;
         struct termios m_session_tty;
         
         void flush( ) const;
   };
}




#endif  // _SERIAL_HPP_
