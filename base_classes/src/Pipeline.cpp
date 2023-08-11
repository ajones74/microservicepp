#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>

#include <unistd.h>

#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>

namespace mspp {


   // The data SOURCE is always at the beginning of the vector.
   void Pipeline::add_source( std::unique_ptr< Section > &&section )
   {
      m_sections.insert( m_sections.begin(), std::move( section ) );
   }

   // All filters/mappers/transforms/etc are appended after the 
   // data SOURCE.
   void Pipeline::add_section( std::unique_ptr< Section > &&section )
   {
       m_sections.push_back( std::move(section) );
   }

   // Ensure that the data sink (almost always an NNG Socket) is 
   // at the END of the vector.
   void Pipeline::add_sink( std::unique_ptr< Section > &&section )
   {
      m_sections.insert( m_sections.end(), std::move( section ) );
   }

#if 0
   // ///////////////////////////////////////////////////////////
   //
   //
   //
   //
   void Pipeline::connect_to_logging_service( )
   {
      int rv;

      // TODO: This shouldn't be hardcoded and/or limitted to local scope
      const std::string service_URL = "ipc:///tmp/service/logging.ipc";

      if ( ( rv = nng_push0_open( &m_logging_socket ) ) != 0)
      {
         std::stringstream iss;
         iss << __FUNCTION__ << ": nng_push0_open() - (" << rv << ")";
         throw mspp_startup_exception( iss.str() );
      }

      // N.B: "nng_dial()" BOTH crates and STARTS the dialer --
      //      maybe I want to do a "nng_dialer_create()", followed
      //      with a "nng_dialer_start()", LATER?????
      //
      // N.B: NNG_FLAG_NONBLOCK flag to nng_dial() can help an application
      // be more resilient, it also generally makes diagnosing failures 
      // somewhat more difficult.
      if ( ( rv = nng_dial( m_logging_socket,
                            service_URL.c_str(),
                            NULL,
                            NNG_FLAG_NONBLOCK ) ) != 0)
      {
         std::stringstream iss;
         iss << __FUNCTION__ 
            << ": nng_dial() - (" 
            << rv 
            << "), ("
            << service_URL 
            << ")" 
            << std::endl;
         throw mspp_startup_exception( iss.str() );
      }

      // Let's send a greeting to the logging service!
      //
      std::stringstream greeting;
      greeting << "hello, from process PID(" 
               << (int)getpid() 
               << ")" 
               << std::endl;
      if ( ( rv = nng_send( m_logging_socket,
                            (void *)greeting.str( ).c_str( ),
                            greeting.str().length()+1,
                            0 ) ) != 0 )
      {
         std::stringstream iss;
         iss << __FUNCTION__ << ": nng_send() - (" << rv << ")";
         throw mspp_startup_exception( iss.str() );
      }

      // TODO: Associate the nng socket with a logging object, where
      // logging to the service is an aesthetic veneer:
      //
      //  m_logger.log( "Something Bad happened" );  --> logging service.
   }
#endif

#if 0
   void Pipeline::connect_to_configuration_service( )
   {
      int rv;

      // TODO: This shouldn't be hardcoded and/or limitted to local scope
      const std::string service_URL = "ipc:///tmp/service/configuration.ipc";
      if ( ( rv = nng_req0_open( &m_configuration_socket ) ) != 0)
      {
         std::stringstream iss;
         iss << __FUNCTION__ << ": nng_req0_open() - (" << rv << ")";
         throw mspp_startup_exception( iss.str() );
      }
      // N.B: "nng_dial()" BOTH crates and STARTS the dialer --
      //      maybe I want to do a "nng_dialer_create()", followed
      //      with a "nng_dialer_start()", LATER?????
      //
      // N.B: NNG_FLAG_NONBLOCK flag to nng_dial() can help an application
      // be more resilient, it also generally makes diagnosing failures 
      // somewhat more difficult.
      if ( ( rv = nng_dial( m_configuration_socket,
                            service_URL.c_str(),
                            NULL,
                            NNG_FLAG_NONBLOCK ) ) != 0)
      {
         std::stringstream iss;
         iss << __FUNCTION__ << ": nng_dial() - (" 
             << rv << "), ("
             << service_URL << ")" << std::endl;
         throw mspp_startup_exception( iss.str() );
      }
      // Send a REQUEST for configuration with a message that looks like:
      //
      //  "get/configuration/service/GPS"  -or -
      //  "get/configuration/section/GPS_port"  
      //
      std::stringstream greeting;
      greeting << "get/configuration/service/"
               << m_parser.query_string_value( "service" )
               << std::endl;
      if ( ( rv = nng_send( m_configuration_socket,
                            (void *)greeting.str( ).c_str( ),
                            greeting.str().length()+1,
                            0 ) ) != 0 )
      {
         std::stringstream iss;
         iss << __FUNCTION__ << ": nng_send() - (" << rv << ")";
         throw mspp_startup_exception( iss.str() );
      }
      // Get the RESPONSE -- a JSON-structured document
      // for the configuration for this service:
      //
      size_t buf_size = 0;
      char *buf = nullptr;
      if ( ( rv = nng_recv( m_configuration_socket,
                            &buf, 
                            &buf_size,
                            NNG_FLAG_ALLOC ) ) != 0 )
      {
         std::stringstream iss;
         iss << __FUNCTION__ << ": nng_recv( ) - (" << rv << ")";
         throw mspp_startup_exception( iss.str() );
      }
      // Can I safely assume this response is NUL-terminated???
      if ( buf[buf_size] != 0 )
      {
         std::stringstream iss;
         iss << __FUNCTION__ 
             << ": nng_recv( ) - malformed or non-null-terminated string."
             << std::endl;
         throw mspp_startup_exception( iss.str() );
      }
      // move the received response into a std::string, to be fetched later
      // using the ::pul() or ::pull (std::string) functions:
      m_pulled_configuration = std::string{buf}; 
      // Free the heap-allocated memory allocated by the nng_recv()
      // call.
      nng_free( buf, buf_size );
   }
#endif 

}
