#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

#include <spdlog/async.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <nng/nng.h>
#include <nng/protocol/pipeline0/push.h>

namespace mspp {
   class Logging {
      public:
         // TODO: Consider delete'ing this default ctor...
         Logging();
         Logging(const std::string &logging_file_name);
         virtual ~Logging();

         static Logging *instance();
         
         virtual void connect( );

         void debug(const std::string &msg);
         void debug(const char *msg, size_t len);

         void info(const std::string &msg);
         void info(const char *msg, size_t len);

         void warn(const std::string &msg);
         void warn(const char *msg, size_t len);

         void error(const std::string &msg);
         void error(const char *msg, size_t len);

         void set_log_level(uint8_t level);
         void set_log_level(uint8_t level, uint32_t mask);
         uint8_t get_log_level() const { return m_log_level; }
         uint32_t get_log_mask() const { return m_log_mask; }

      private:
         uint8_t m_log_level;
         uint32_t m_log_mask;
         // spdlog::sinks::rotating_file_sink_mt m_file_logger;
         std::string m_ipc_link_string;
         nng_socket m_nng_logging_sock;
         // TODO: THIS *must* become "std::atomic_bool"
         bool m_connected;

         static Logging *m_instance;
         static std::string m_logfile_name;
         static std::chrono::steady_clock::time_point m_start_time;

         bool push( const std::string &msg );
         bool push( const char *msg, size_t len );
   };
}  // namespace mspp
#endif  // _LOGGING_HPP_
