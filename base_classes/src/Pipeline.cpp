#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>

#include <unistd.h>

#include <mspp_exceptions.hpp>
#include <Pipeline.hpp>
#include <SLP_Parser.hpp>

namespace mspp {

   Pipeline::Pipeline( const std::string &connection_string ) :
      m_connection_string{ connection_string }
   {
      m_parser.set( m_connection_string );
   }

   // throws a runtime exception if the connection
   // to a service or other pump fails.
   void Pipeline::connect( )
   {
      // Most primitive tests for a valid connection string
      m_parser.parseable( );

      // Decompose the connection string into constituent tokens
      m_parser.tokenize_connection_string( ); 

      // Parse the query string (everything after the '?', just as if
      // the connection string were an HTTP URL) of the connection string
      // into a key-value map
      m_parser.tokenize_query_string( );

      const std::string primary_resource{ m_parser.primary_resource( ) };
      if ( primary_resource == "service" )
      {
         // Connect to a (remote/local) service...
         connect_to_service( );
      } else if ( primary_resource == "section" )
      {
         // Connect to a pipe section...
         connect_to_section( );
      } else
      {
         std::string msg = "Malformed/invalid service:(" + primary_resource + ")";
         throw mspp_startup_exception( msg );
      }
   }

   std::string Pipeline::pull( )
   {
      return m_pulled_configuration; 
   }

   // Pull a work-item form the end port of the pipeline, in a 
   // format/encoding specified in the string:
   //  "format=std::string"  (default)
   //  "format=JSON"
   //  "format=XML"
   //  "format=msgpack"
   //  "encode=UTF-8"
   //  "encode=UTF-32", etc.
   std::string Pipeline::pull( const std::string &format )
   {
      return m_pulled_configuration; 
   }

   // Throws an exception if the connection to the SERVICE fails.
   void Pipeline::connect_to_service( )
   {
      // Using the secondary resource identified in the SLP_Parser,
      // use it to connect via IPC to something like:
      //
      //   ipc:///tmp/service/<SECONDARY_RESOURCE_NAME>.ipc
      const std::string service_name = m_parser.secondary_resource( );
      const std::string IPC_service = "/tmp/service/" +  
                                      service_name + 
                                      ".ipc";

      // As we are the CLIENT/DIALLER, we don't want to create the IPC
      // file -- this is the responsibility of the .run() method in the
      // Service class.
      // If the IPC file does NOT exist, Bail.
      //
      // NOTE: This may not be a good policy. I'm okay in removing it
      //       if it is a headache...
      std::filesystem::path service_path{ IPC_service };

      if ( std::filesystem::exists( service_path ) == false )
      {
         std::string msg = "IPC file not found(" + IPC_service + ")";
         throw mspp_startup_exception( msg );
      }


      //  ---- CONNECT TO A SERVICE -----
      //
      // The easy services are the LOGGING and CONFIGURATION services --
      // Their ROLE (dial/connect) and PATTERN (REQREP, PUSHPULL, PUBSUB, etc)
      // are already known:
      //   * LOGGING(SERVER) --> LISTEN and PULL
      //   * LOGGING(CLIENT) --> DIAL and PUSH
      //   * CONFIG(SERVER)  --> LISTEN and REPLY
      //   * CONFIG(CLIENT)  --> DIAL and REQUEST
      //
      // Any other services (GPS, IMU, RFM, etc) will FIRST require a 
      // connection to the configuration service to REQUEST a copy of its
      // own configuration to assign contexts and other runtime settings.
      // 
      //

      if ( service_name == "logging" )
      {
         connect_to_logging_service(  );
      } else if ( service_name == "configuration" )
      {
         connect_to_configuration_service( );
      } else {
         // This is a custom or extended service that requires a
         // GET/CONFIGURATION/SERVICE/<SERVICE_NAME>/MAIN request to the
         // configuration service -- store the results in this Pipelines'
         //
         connect_to_custom_service( );
      }

   }

   void Pipeline::connect_to_section( )
   {

   }


   //   * LOGGING(CLIENT) --> DIAL and PUSH
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


   //
   //   * CONFIG(CLIENT)  --> DIAL and REQUEST
   //
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
      if ( ( rv = nng_recv(  m_configuration_socket,
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
      // Now, free the heap-allocated memory allocated by the nng_recv()
      // call.
      nng_free( buf, buf_size );
   }

   void Pipeline::connect_to_custom_service( )
   {
      std::string msg = std::string{__FUNCTION__} + std::string{": UNIMPLEMENTED."}; 
      throw mspp_startup_exception( msg );
   }
}
