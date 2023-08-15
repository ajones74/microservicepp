#ifndef _SECTION_HPP_
#define _SECTION_HPP_

#include <iostream>
#include <string>
#include <map>
#include <atomic>
#include <thread>

#include <Logging.hpp>

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
         Logging m_log;

         std::thread m_thread;
         std::string m_init_string;
         std::map<std::string, std::string> m_init_pairs;

         // The IPC string (or connection string!) 
         // for the data SOURCE port. Required.
         std::string m_source_string;
         // The IPC string for the data SINK port. Required.
         std::string m_sink_string;
         // The IPC string for the "command and control" port.
         std::string m_control_string;
   };
}



#endif  // _SECTION_HPP_
