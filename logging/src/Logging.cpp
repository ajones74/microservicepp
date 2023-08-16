#include <chrono>
#include <iostream>

#include <Logging.hpp>

#include <syslog.h>

namespace mspp 
{
   Logging *Logging::m_instance = nullptr;
   std::string Logging::m_logfile_name{"/tmp/logging.out"};
   std::chrono::steady_clock::time_point Logging::m_start_time = std::chrono::steady_clock::now(); 

   Logging::Logging( ) 
   {
      // DEFAULT: Log to syslogd, or whatever systemd uses for system logging.
      openlog( (const char *)0,
               LOG_CONS | LOG_PID, // Log to CONSOLE on syslogd error, include PID
               LOG_USER );

   }
   
   Logging::Logging( const std::string &logging_file_name ) 
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

      // TODO: Cleanup/release/delete any allocated resources.
      delete m_instance;

      m_instance = nullptr;
      // Close socket to syslogd.
      closelog( );
   }

   Logging *Logging::get( )
   {
      if ( m_instance == nullptr )
      {
         m_instance = new Logging( m_logfile_name );
         m_start_time = std::chrono::steady_clock::now();
      }  
      return m_instance;
   }

   void Logging::debug( const std::string &msg )
   {
      syslog( LOG_DEBUG, "%s", msg.c_str( ) ); 
   }

   void Logging::debug( const char *msg )
   {
      syslog( LOG_DEBUG, "%s", msg ); 
   }

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
