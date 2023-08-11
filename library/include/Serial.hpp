#ifndef _SERIAL_HPP_
#define _SERIAL_HPP_

#include <iostream>

#include <cstddef>
#include <unistd.h>

namespace mspp {

   class Serial {
      public: 
         ~Serial( );

         bool open( );
         void close( );
         
         int read(  char *data, size_t len );
         int read(  const std::string );
         
         int write( const char *data, size_t len );
         int write( const std::string );
  
      protected:
      private:
         int m_fd;
         
         void flush( );
   };
}




#endif  // _SERIAL_HPP_
