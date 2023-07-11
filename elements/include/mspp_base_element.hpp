#ifndef _MSPP_BASE_ELEMENT_HPP_
#define _MSPP_BASE_ELEMENT_HPP_

#include <string>
#include <vector>

#include <mspp_base_pad.hpp>

namespace mspp {
    class mspp_base_element {
        public:
            // NO default ctor.
            mspp_base_element( ) = delete;

            explicit mspp_base_element( const std::string name )
                : m_descriptive_name{name} {};

            virtual ~mspp_base_element( ) = 0;

            virtual bool add_source_pad( mspp_base_pad &source );
            virtual bool add_sink_pad( mspp_base_pad &sink );

        private:
            std::string m_descriptive_name;
    };




}



#endif // _MSPP_BASE_ELEMENT_HPP_
