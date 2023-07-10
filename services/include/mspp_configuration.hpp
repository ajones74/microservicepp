#ifndef _MSPP_CONFIGURATION_HPP_
#define _MSPP_CONFIGURATION_HPP_

#include <mspp_base.hpp>

namespace mspp {

    class mspp_configuration : public mspp_base {
        public:
            // NO default ctor
            mspp_configuration( ) = delete;

            mspp_configuration( int argc, const char **argv );

            ~mspp_configuration( );

            virtual bool start_service( );
            virtual bool stop_service( );
    };

}

#endif // _MSPP_CONFIGURATION_HPP_
