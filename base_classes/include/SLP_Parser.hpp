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

      void tokenize_connection_string( );
      
      void tokenize_query_string( );

      std::string primary_resource( ) const;

      std::string secondary_resource( ) const;

      std::string query_string_value( const std::string &key ) const;

   private:
      // protocol://host/primary_resource/secondary_resource?key1=value1&key2=value2&...
      std::string m_connection_string;
      
      // decompose the connection string into its basic tokens:
      // * protocol
      // * host  ( . or 127.0.0.1 or localhost or IP-address or FQDN.
      // * primary resource  (service or section)k
      // * secondary resource (logging, configuration, GPS, etc)
      // * key-value pairs of the query string are parsed ELSEWHERE.
      std::map<std::string, std::string> string_tokens;

      // A mapping of all of the key-value pairs in the query-string
      std::map<std::string, std::string> query_string_pairs;

};


}




#endif // _SLP_PARSER_HPP_
