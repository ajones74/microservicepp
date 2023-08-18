#include <iostream>


#include <GPS.hpp>


namespace mspp 
{
   GPS *GPS::m_instance = nullptr;

   GPS::~GPS( ) {
      if ( m_instance == nullptr ) {
         return;
      }
      delete m_instance;
      m_instance = nullptr;
   }

   GPS *GPS::instance() {
      if (m_instance != nullptr) {
         return m_instance;
      }
      m_instance = new GPS;
      return m_instance;
   }

   // bind() will:
   // * Create an instance of the Serial class to connect to ttymxc2 for the GPS
   // * Create the NNG socket that will:
   // ** LISTEN for connections, and 
   // ** PUSH data
   //
   // NOTE:
   //    The GPS Agent class wil create an NNG socket that will:
   //    ** DIAL to connect, and
   //    ** PULL data
   bool GPS::bind( const std::string &ipc_str ) {
      // TODO: validate that this is an IPC URI in the right format/structure.
      m_ipc_string = ipc_str;

      return true;
   }


}

