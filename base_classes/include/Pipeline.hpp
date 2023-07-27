#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <string>
#include <vector>
#include <map>

#include <Section.hpp>
#include <SLP_Parser.hpp>
#include <nlohmann/json.hpp>

#include <nng/nng.h>
#include <nng/protocol/pipeline0/push.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

namespace mspp {
class Pipeline {
   public:
      Pipeline( ) = delete;
      Pipeline( const std::string &connection_string );
      void connect( ); 
      std::string pull( );
      std::string pull( const std::string &format );

   private:
      //
      // MEMBERS
      // 
      std::string m_connection_string;
      nlohmann::json m_system_configuration;

      SLP_Parser m_parser;

      // Every pipeline will have at least one connection, maybe two:
      //  1) To the logging service
      //  2) (Optional) to the configuration service
      nng_socket m_logging_socket;
      nng_socket m_configuration_socket;

      std::map< std::string, nng_socket> m_custom_sockets;

      //
      // METHODS
      //
      void connect_to_service( );
      void connect_to_section( );
      // Connecting to logging and configuration services 
      // may have no access to the system-wide configuration --
      // These two services have to be "boot strapped"
      void connect_to_logging_service( );
      void connect_to_configuration_service( );
      // Custom/other services are detailed in the system-wide
      // configuration in JSON format using the m_system_configuration 
      // JSON object:
      void connect_to_custom_service( );


};

}

#endif // _PIPELINE_HPP_
