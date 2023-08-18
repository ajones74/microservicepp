#ifndef __GPS_HPP_
#define __GPS_HPP_

#include <string>
namespace mspp 
{
   class GPS 
   {
   public:
      virtual ~GPS();

      static GPS *instance( );
      bool bind( const std::string &ipc_str );

   protected: 
      static GPS *m_instance;

      std::string m_ipc_string;
   private:
      GPS() {}

   };
}
#endif // __GPS_HPP_

