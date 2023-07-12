#ifndef _MSPP_BASE_HPP_
#define _MSPP_BASE_HPP_

#include <string>
#include <vector>
#include <mspp_base_element.hpp>

namespace mspp {
   class mspp_base_service {
      public:
         // NO default constructors!
         //mspp_base_service( ) = delete;     
         
         // EXPLICIT single-arg constructor
         //explicit mspp_base_service( const std::string name ) 
         //   : m_descriptive_name{name} {};

         // To force derived classes to cleanup their messes...
         //virtual ~mspp_base_service( ) = 0; 

         virtual bool add_source( mspp_base_element &source );
         virtual bool add_sink( mspp_base_element &sink ); 
         
         virtual bool start_service( ) = 0;
         virtual bool stop_service( ) = 0;


      private:
         std::string m_descriptive_name;
         std::vector<mspp_base_element> m_sources;
         std::vector<mspp_base_element> m_sinks;
   };
}

#endif // _MSPP_BASE_HPP_
