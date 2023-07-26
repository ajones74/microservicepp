#include <iostream>
#include <string>
#include <filesystem>

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
      //
      const std::string service_name = m_parser.secondary_resource( );
      const std::string IPC_service = "/tmp/service/" +  
                                      service_name + 
                                      ".ipc";
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

      if ( 





   }

   void Pipeline::connect_to_section( )
   {

   }



}
