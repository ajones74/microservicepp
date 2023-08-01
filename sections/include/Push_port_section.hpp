#ifndef _PUSH_PORT_SECTION_HPP_
#define _PUSH_PORT_SECTION_HPP_ 

#include <Section.hpp>

namespace mspp {
   class Push_port_section : public Section {
      public:
         Push_port_section( const std::string &init_string ) :
            Section{ init_string } 
         { }

         virtual void start( );

         virtual void stop( );

      private:

   };
}
#endif   // _PUSH_PORT_SECTION_HPP_ 
