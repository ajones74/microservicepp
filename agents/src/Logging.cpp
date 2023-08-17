#include "nng/protocol/pipeline0/push.h"
#include <chrono>
#include <iostream>

#include <Logging.hpp>

#include <syslog.h>

namespace mspp 
{
   Logging *Logging::m_instance = nullptr;
   std::string Logging::m_logfile_name{"/tmp/logging.out"};
   std::chrono::steady_clock::time_point Logging::m_start_time = std::chrono::steady_clock::now(); 

   Logging::Logging( ) : 
      m_connected{false}
   {
      // DEFAULT: Log to syslogd, or whatever systemd uses for system logging.
      openlog( (const char *)0,
               LOG_CONS | LOG_PID, // Log to CONSOLE on syslogd error, include PID
               LOG_USER );

   }
   
   Logging::Logging( const std::string &logging_file_name ) :
      m_connected{false}
   {
      // DEFAULT: Log to syslogd, or whatever systemd uses for system logging.
      openlog( (const char *)0,
               LOG_CONS | LOG_PID, // Log to CONSOLE on syslogd error, include PID
               LOG_USER );

   }

   Logging::~Logging( ) 
   {
      if ( m_instance  == nullptr )
      {
         return;
      }

      delete m_instance;
      m_instance = nullptr;
      // Close socket to syslogd.
      closelog( );

      if (m_connected)
      {
         nng_close( m_nng_logging_sock );
         m_connected = false;
      }  
   }

   Logging *Logging::instance( )
   {
      if ( m_instance )
      {
         return m_instance;
      }

      // Else, we gotta lot of work to do! 
      m_start_time = std::chrono::steady_clock::now();
      
      m_instance = new Logging( m_logfile_name );
      return m_instance;
   }

   // 1) Create nng socket to connect to the Logging SERVICE
   //   the SERVICE employs ( listen and pull )
   //  2) Our AGENT employs ( dial and push  )   
   //
   void Logging::connect( )
   {
      int retval = 0;

      if (m_connected)
      {
         return;
      }
      if ( (retval = nng_push0_open(&m_nng_logging_sock)) != 0)
      {
         // TODO: Log the err-msg to syslog with retval value
         return;
      }
      if ( (retval = nng_dial( m_nng_logging_sock, m_ipc_link_string, NULL, 0)) != 0)
      {
         // TODO: Log the err-msg to syslog with retval value
         return;
      }
      m_connected = true;      
   }


   void Logging::debug( const std::string &msg )
   {
      syslog( LOG_DEBUG, "%s", msg.c_str( ) ); 
   }

   void Logging::debug( const char *msg )
   {
      syslog( LOG_DEBUG, "%s", msg ); 
   }

   // 1) Unconditionally (???) log to syslog..
   // 2) take the msg and write it to the nng socket 
   //    created in the .connect() method.   
   void Logging::info( const std::string &msg )
   {
      syslog( LOG_INFO, "%s", msg.c_str( ) ); 
   }

   void Logging::info( const char *msg )
   {
      syslog( LOG_INFO, "%s", msg ); 
   }

   void Logging::warn( const std::string &msg )
   {
      syslog( LOG_WARNING, "%s", msg.c_str( ) ); 
   }

   void Logging::warn( const char *msg )
   {
      syslog( LOG_WARNING, "%s", msg ); 
   }

   void Logging::error( const std::string &msg )
   {
      syslog( LOG_ERR, "%s", msg.c_str( ) ); 
   }

   void Logging::error( const char *msg )
   {
      syslog( LOG_ERR, "%s", msg ); 
   }

   void Logging::set_log_level( uint8_t level )
   {
      // TODO: range-check the argument.
      m_log_level = level;
   }

   void Logging::set_log_level( uint8_t level, uint32_t mask )
   {
      // TODO: range-check the arguments.
      m_log_level = level;
      m_log_mask  = mask; 
   }

}
