#ifndef _MSPP_BASE_HPP_
#define _MSPP_BASE_HPP_

#include <string>
#include <vector>
#include <mspp_pad.hpp>

namespace mspp {
   class mspp_base {
      public:
         // NO default constructors!
         mspp_base( ) = delete;     
         // EXPLICIT single-arg constructor
         explicit mspp_base( const std::string name ) 
            : m_descriptive_name{name} {};
         // To force derived classes to cleanup their messes...
         virtual ~mspp_base( ) = 0; 

         virtual bool add_source( mspp_pad &source );
         virtual bool add_sink( mspp_pad &sink ); 
         
         virtual bool start( ) = 0;
         virtual bool stop( ) = 0;
         virtual bool initialize( ) = 0;

      private:
         std::string m_descriptive_name;
         std::vector<mspp_pad> m_sources;
         std::vector<mspp_pad> m_sinks;
   };
}

#endif // _MSPP_BASE_HPP_
