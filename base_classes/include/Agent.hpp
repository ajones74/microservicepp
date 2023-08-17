#ifndef _AGENT_HPP_
#define _AGENT_HPP_

#include <iostream>
#include <string>
#include <vector>

namespace mspp 
{
   class Agent {
      public:
         Agent( const std::string &init_str ) :
            m_init_string{init_str}
         { }
         virtual ~Agent();

         // This might be a bad polymorphic idea...
         static Agent *instance();
   
         // Every derived class needs to "connect()"
         virtual void connect( ); 
         virtual void connect( const std::string &init_string );
      
         // This will "link" the PUSH side of an agent to the PULL side of an 
         // agent via an IPC string, something like:
         //   "ipc:///tmp/agents/gps_serial_to_NMEA_filter.ipc"
         //
         // NOTE:
         // The IPC string is pretty free-form -- constrained only to using a valid
         // filesystem structure on the computer running this program...
         virtual bool link ( Agent &push_agent, Agent &pull_agent, const std::string &ipc_link_string );
  
         // On-demand Producer/Consumer agents, like Logging and 
         // Configuration don't have a producer-consumer loop and
         // hence may not need to support the start() or stop() methods.
         virtual void start( );
         virtual void stop( );

         // Free-running Producer/Consumer agents, like GPS and RFM
         // have a producer-consumer loop and hence may not need 
         // to support the push() or pull() methods --
         //
         // Useful for pushing binary messages -- msgpack, protobufs,
         // Flatbuffers, cppack, etc.
         virtual bool push( const std::vector<std::byte> &payload );

         // Useful for pushing structured text  -- JSON, XML, etc:
         // * "format=JSON"
         // * "format=std::string" (default)
         // * "format=XML"
         // * "encode=UTF-8"
         // * "encode=UTF-32",
         // * etc.
         virtual bool push( const std::string &format, const std::string &payload );

         // Useful for pulling structured text  -- JSON, XML, etc:
         // * "format=JSON"
         // * "format=std::string" (default)
         // * "format=XML"
         // * "encode=UTF-8"
         // * "encode=UTF-32",
         // * etc.
         virtual std::string pull( const std::string &format );

         // Useful for pulling binary messages -- msgpack, protobufs,
         // Flatbuffers, cppack, etc.
         virtual std::vector<std::byte> pull( );

         
      protected:
         std::string m_init_string;

         static Agent *m_instance;

      private:
         Agent() {}
   };
}
#endif  // _AGENT_HPP_





