#ifndef _SLP_PARSER_HPP_
#define _SLP_PARSER_HPP_

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
      // The string to parse (str_to_parse) should conform
      // as much as possible to RFC2608 -- some valid examples:
      // *  "pipeline://./service/configuration?flow=pull&format=JSON"
      // *  "service://./service/GPS"
      void parseable( const std::string &str_to_parse );


   private:
};


}




#endif // _SLP_PARSER_HPP_
