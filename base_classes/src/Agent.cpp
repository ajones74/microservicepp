#include <iostream>
#include <algorithm>


#include <Agent.hpp>
#include <iterator>


namespace mspp 
{
   Agent *Agent::m_instance = nullptr;

   Agent::~Agent( )
   {
      if ( m_instance == nullptr )
      {
         return;
      }
      delete m_instance;
      m_instance = nullptr;
   }

   Agent *Agent::instance( )
   {
      if (m_instance) 
      {
         return m_instance;   
      }
      m_instance = new Agent("Generic Agent");
      return m_instance;
   }

   void Agent::connect( )
   {

   }

   void Agent::connect( const std::string &init_string )
   {
      m_init_string = init_string;
      connect();
   }

   void Agent::stop( )
   {

   }

   void Agent::start( )
   {

   }

   bool Agent::push( const std::vector<std::byte> &payload )
   {
      return true;
   }

   bool Agent::push( const std::string &format, const std::string &payload )
   {
      return true;
   }

   std::string Agent::pull( const std::string &format )
   {
      return std::string("Unimplemented");
   }

   std::vector<std::byte> Agent::pull( )
   {
      std::string tmp{"Unimplemented"};

      std::vector<std::byte> retval;

      retval.reserve( tmp.size()+1);

      std::transform( tmp.begin(),
                      tmp.end(), 
                      std::back_inserter(retval), 
                      [] (const char c) { return std::byte(c); } );

      return retval;
   }
}
