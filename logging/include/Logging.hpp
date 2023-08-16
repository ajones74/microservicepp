#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

#include <chrono>
#include <spdlog/async.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <sstream>
#include <string>

namespace mspp {
   class Logging {
      public:
         Logging();
         Logging(const std::string &logging_file_name);
         ~Logging();

         static Logging *get();

         void debug(const std::string &msg);
         void debug(const char *msg);

         void info(const std::string &msg);
         void info(const char *msg);

         void warn(const std::string &msg);
         void warn(const char *msg);

         void error(const std::string &msg);
         void error(const char *msg);

         // template< typename T >
         // Logging &operator<< ( Logging &rhs, T value )
         // {
         //    rhs.m_log_msg << value;
         //    return rhs;
         // }

         void set_log_level(uint8_t level);
         void set_log_level(uint8_t level, uint32_t mask);
         uint8_t get_log_level() const { return m_log_level; }
         uint32_t get_log_mask() const { return m_log_mask; }

      private:
         uint8_t m_log_level;
         uint32_t m_log_mask;
         // spdlog::sinks::rotating_file_sink_mt m_file_logger;
         std::stringstream m_log_msg;

         static Logging *m_instance;
         static std::string m_logfile_name;
         static std::chrono::steady_clock::time_point m_start_time;
   };
}  // namespace mspp
#endif  // _LOGGING_HPP_
