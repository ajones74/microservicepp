#include <iostream>

#include <Logging.hpp>

namespace mspp 
{
   Logging *Logging::m_instance = nullptr;

   Logging::Logging( ) 
   {

   }
   
   Logging::~Logging( ) 
   {

   }

   Logging * Logging::instance( )
   {

      return nullptr;
   }

   void Logging::write( const std::string &msg )
   {

   }

   void Logging::write( const char *msg )
   {

   }


   void Logging::set_log_level( uint8_t level )
   {
      // TODO: range-check the argument.
      m_log_level = level;
   }

   void Logging::set_log_level( uint8_t level, uint32_t mask )
   {
      // TODO: range-check the arguments.
      m_log_level = level;
      m_log_mask  = mask; 
   }

}
