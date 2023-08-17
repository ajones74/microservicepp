#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <atomic>

#include <nng/nng.h>

namespace mspp 
{
   class Configuration 
   {
      public:
         virtual ~Configuration(); 

         static Configuration *instance( );

         virtual void connect( );

         virtual std::string pull( const std::string &format_string );
         virtual std::vector<std::byte> pull( );
         virtual bool push( const std::string &format, const std::string &payload );
         virtual bool push( const std::vector<std::byte> &payload );

      protected:

      private:
         std::string m_ipc_link_string;
         nng_socket m_nng_config_sock;

         static std::atomic_bool m_connected;
         static Configuration *m_instance;

         // HIDE the default ctor!
         Configuration() {}
   };
}
#endif  // _CONFIGURATION_HPP_
