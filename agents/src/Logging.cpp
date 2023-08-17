#include "nng/nng.h"
#include "nng/protocol/pipeline0/push.h"
#include <chrono>
#include <iostream>

#include <Logging.hpp>

#include <sys/syslog.h>
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
         syslog( LOG_ERR, "%s:%s: error on open(%s)", __FILE__, __FUNCTION__, nng_strerror(retval) );
         return;
      }
      if ( (retval = nng_dial( m_nng_logging_sock, m_ipc_link_string.c_str(), NULL, 0) ) != 0 )
      {
         syslog( LOG_ERR, "%s:%s: error on dial(%s)", __FILE__, __FUNCTION__, nng_strerror(retval) );
         return;
      }
      m_connected = true;      
   }


   bool Logging::push( const char *msg, size_t len )
   {
      int retval;
      // NOTE: We are sending the message WITHOUT the nul-termination
      // byte! This might be a nerd trap on the receiver...
      if ( (retval = nng_send( m_nng_logging_sock, 
                               (void *)msg, 
                               len, 
                               NNG_FLAG_NONBLOCK )) != 0 )
      {
         syslog( LOG_WARNING, "Logging::push(): error(%s)", nng_strerror(retval) );
         return false;
      }
      return true;   
   }

   bool Logging::push( const std::string &msg )
   {  
      return push( msg.c_str(), msg.size() );
   }

   void Logging::debug( const std::string &msg )
   {
      syslog( LOG_DEBUG, "%s", msg.c_str( ) );
      push( msg );
   }

   void Logging::debug( const char *msg, size_t len )
   {
      syslog( LOG_DEBUG, "%s", msg ); 
      push( msg, len );
   }

   // 1) Unconditionally (???) log to syslog..
   // 2) take the msg and write it to the nng socket 
   //    created in the .connect() method.   
   void Logging::info( const std::string &msg )
   {
      syslog( LOG_INFO, "%s", msg.c_str( ) );
      push( msg );
   }

   void Logging::info( const char *msg, size_t len )
   {
      syslog( LOG_INFO, "%s", msg );
      push( msg, len );      
   }

   void Logging::warn( const std::string &msg )
   {
      syslog( LOG_WARNING, "%s", msg.c_str( ) ); 
      push( msg );
   }

   void Logging::warn( const char *msg, size_t len )
   {
      syslog( LOG_WARNING, "%s", msg ); 
      push( msg, len );
   }

   void Logging::error( const std::string &msg )
   {
      syslog( LOG_ERR, "%s", msg.c_str( ) ); 
      push( msg );
   }

   void Logging::error( const char *msg, size_t len )
   {
      syslog( LOG_ERR, "%s", msg ); 
      push( msg, len );
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
