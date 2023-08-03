#ifndef _SECTION_HPP_
#define _SECTION_HPP_

#include <iostream>
#include <string>
#include <map>
#include <atomic>
#include <thread>

namespace mspp {

   class Section 
   {
      public:
         Section( const std::string &init_string ) :
            m_init_string{ init_string }
         { 
            m_started.store( false );
            m_connected.store( false );
         }
         virtual void connect( ) = 0;
         virtual void start( ) = 0;
         virtual void stop( ) = 0;
      protected:
         std::atomic_bool m_started;
         std::atomic_bool m_connected; 

         std::thread m_thread;
         std::string m_init_string;
         std::map<std::string, std::string> m_init_pairs;
         
   };
}



#endif  // _SECTION_HPP_
