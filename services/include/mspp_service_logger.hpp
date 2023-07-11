#ifndef _MSPP_LOGGER_HPP_
#define _MSPP_LOGGER_HPP_

#include <mspp_base_service.hpp>


namespace mspp {
    class mspp_logger : public mspp_base_service {
    public:
        // NO default ctor.
        mspp_logger( ) = delete;
        
        explicit mspp_logger( const std::string &src_uri );

        bool start_service( );
        bool stop_service( );

    private:

    };
}
#endif // _MSPP_LOGGER_HPP_
