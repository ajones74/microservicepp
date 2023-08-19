#include <iostream>
#include <algorithm>

#include <Configuration_Agent.hpp>


namespace mspp 
{
   Configuration *Configuration::m_instance = nullptr;
   std::atomic_bool Configuration::m_connected = false; 

   Configuration::~Configuration( )
   {

   }

   Configuration *Configuration::instance( )
   {
      if (m_instance != nullptr)
      {
         return m_instance;
      }
      m_instance = new Configuration;
      m_connected.store(true);
      
      return m_instance;
   }

   void Configuration::connect( )
   {

   }

   std::string Configuration::pull( const std::string &format_string )
   {
      return std::string{"unimplemented"};
   }

   std::vector<std::byte> Configuration::pull( )
   {
      std::string str{"unimplemented"};

      std::vector<std::byte> tmp;
      tmp.reserve( str.size() );

      std::transform( str.begin(), 
                      str.end(), 
                      std::back_inserter(tmp), 
                     [] (const char c) { return std::byte(c); } );

      return tmp;
   }

   bool Configuration::push( const std::string &format, const std::string &payload )
   {
      return false;
   }

   bool Configuration::push( const std::vector<std::byte> &payload )
   {
      return false;
   }
}
