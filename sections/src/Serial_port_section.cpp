#include <iostream>

#include <Serial_port_section.hpp>

namespace mspp {

   void Serial_port_section::connect( )
   {

   }

   void Serial_port_section::start( )
   {
      if ( m_started )
      {
         return;
      }

      // 1) Open the serial port
      // 2) Initiate NNG resources
      // 3) create a std::thread with a private function
      // 4) SUCCESS!
      //
      if ( false == open_serial_port( ) ) 
      {
         // error
      
      }

      if ( false == open_nng_sockets( ) )
      {
         // error
      
      }
      m_started = true;
   }

   void Serial_port_section::stop( )
   {
      if ( m_started == false )
      {
         return;
      }


      m_started = false;
   }

   bool Serial_port_section::open_serial_port( )
   {
      bool passed = false;

      return passed;
   }
 
   bool Serial_port_section::open_nng_sockets( )
   {
      bool passed = false;

      return passed;
   }





}
