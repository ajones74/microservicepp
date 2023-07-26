#ifndef _SLP_PARSER_HPP_
#define _SLP_PARSER_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <string>


namespace mspp {

/* The EBNF notation for our schema is:

connection-string ::= '"' (
( service '://' ( '.' | localhost | IP-addr | FQDN ) '/service/' (logging | configuration | GPS | IMU | WEB)  ( '?'  ((key '=' value)('&' key '=' value)*)  )? )   | 
(pipeline '://' ( '.' | localhost | IP-addr | FQDN ) '/' ( service '/' ( logging | configuration | GPS | IMU | WEB) | section  '/' ( pump | pool | filter | etc ) ) ( '?'  ((key '=' value)('&' key '=' value)*)  )?        )  | 
( section '://' ( '.' | localhost | IP-addr | FQDN ) '/section/' ( Pump | Pool | Filter | etc )  ( '?'  ((key '=' value)('&' key '=' value)*)  )? )  
) '"'

NOTE: A visual diagram can be generated with the above EBNF @ https://bottlecaps.de/rr/ui
                                                                    //
NOTE: A generated PNG of the connection schema can be found in docs/connection-string.PNG

 */


class SLP_Parser {
   public:

      void set( const std::string &conn_string );
      // Some valid examples:
      // *  "pipeline://./service/configuration?flow=pull&format=JSON"
      // *  "service://./service/GPS"
      void parseable( );

      void tokenize_connection_string( std::vector<std::string> &tokens );
      
      void tokenize_query_string( std::map<std::string, std::string> &map );

      std::string primary_resource( ) const;

      std::string secondary_resource( ) const;

   private:
      std::string m_connection_string;
};


}




#endif // _SLP_PARSER_HPP_
