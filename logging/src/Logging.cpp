#include <iostream>

#include <Logging.hpp>

#include <syslog.h>

namespace mspp 
{
   Logging *Logging::m_instance = nullptr;

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

#if 0
      // BONUS: file-rotating logger with 5MB size (max) and 3 rotated files.
      m_file_logger = spdlog::rotating_logger_mt( "file_logger",
            logging_file_name,     // logging filename
            1024*1024*5,           // 5 MB max filesize
            3 );                   // 3-deep queue of rotated files.
#endif 

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

   Logging *Logging::instance( )
   {
      if ( m_instance == nullptr )
      {
         m_instance = new Logging( "/tmp/fpcm_logging.txt"  );
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
