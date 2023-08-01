#ifndef _SECTION_HPP_
#define _SECTION_HPP_

#include <iostream>
#include <string>
#include <map>

namespace mspp {

   class Section 
   {
      public:
         Section( const std::string &init_string ) :
            m_init_string{ init_string }
         { }

         virtual void start( ) = 0;

         virtual void stop( ) = 0;

      private: 
         std::string m_init_string;
         std::map<std::string, std::string> m_init_pairs;
         
   };
}



#endif  // _SECTION_HPP_
