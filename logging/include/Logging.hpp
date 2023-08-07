#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_ 

#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_sinks.h>


namespace mspp 
{
   class Logging {
      public:
         Logging( );
         ~Logging( );

         Logging *instance( );

         void write( const std::string &msg );
         void write( const char *msg );
         // std::ostringstream &operator<< ();

         void set_log_level( uint8_t level );
         void set_log_level( uint8_t level, uint32_t mask );
         uint8_t get_log_level( ) const { return m_log_level; }
         uint32_t get_log_mask( ) const { return m_log_mask; }
      
      private:
         uint8_t m_log_level;
         uint32_t m_log_mask;

         static Logging *m_instance;
         

   };
}


#endif // _LOGGING_HPP_ 
