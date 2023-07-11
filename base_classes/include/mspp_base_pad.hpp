#ifndef _MSPP_BASE_SOURCE_HPP_
#define _MSPP_BASE_SOURCE_HPP_ 

#include <sys/types.h>   // ssize_t is NOT defined in C++???

namespace mspp {

    class mspp_base_pad {
        public:

           ssize_t read( size_t count );
           ssize_t read_all( );
           ssize_t read_line( );

           ssize_t write( size_t count );
           ssize_t write_all(  );
           ssize_t write_line( );

        private:

    };
}

#endif // _MSPP_BASE_SOURCE_HPP_

