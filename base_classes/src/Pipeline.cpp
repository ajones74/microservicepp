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
      m_parser.tokenize_connection_string( m_conn_string_tokens ); 

      // Parse the query string (everything after the '?', just as if
      // the connection string were an HTTP URL) of the connection string
      // into a key-value map
      m_parser.tokenize_query_string( m_query_string_map );


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

   // Pull the data from the pipeline in the specified format:
   //  * "format=JSON"
   //  * "format=XML"
   //  * "format=default"  (std::string)
   //  * "format=protobuf"  (google protobuf)
   //  * "format=msgpack"  
   std::string Pipeline::pull( )
   {
      std::string ret_val;
      return ret_val; 
   }
   std::string Pipeline::pull( const std::string &format )
   {
      std::string ret_val;
      return ret_val; 
   }

   // Throws an exception if the connection to the SERVICE fails.
   void Pipeline::connect_to_service( )
   {
      // Using the secondary resource identified found in the SLP_Parser,
      // use it to connect via IPC to something like:
      //   ipc:///tmp/service/<SECONDARY_RESOURCE_NAME>.ipc
      const std::string service_name = m_parser.secondary_resource( );
      const std::string IPC_service = "/tmp/service/" +  
                                      service_name + 
                                      ".ipc";

      // As we are the CLIENT/DIALLER, we don't want to create the IPC
      // file -- this is the responsibility of the .run() method in the
      // Service class.
      // If the IPC file does NOT exist. Bail.
      std::filesystem::path service_path{ IPC_service };

      if ( std::filesystem::exists( service_path ) == false )
      {
         std::string msg = "File not found(" + IPC_service + ")";
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
         iss << __FUNCTION__ << ": nng_dial() - (" << rv << ")";
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

   }


   void Pipeline::connect_to_configuration_service( )
   {

   }

   void Pipeline::connect_to_custom_service( )
   {

   }
}
