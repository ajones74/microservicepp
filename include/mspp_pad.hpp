#ifndef _MSPP_PAD_HPP_
#define _MSPP_PAD_HPP_

#include <string>

namespace mspp {

   class mspp_pad {
   public:
      // NO default constructors!
      mspp_pad( ) = delete; 


   private:
      // Because _everything_ in UNIX is a file. ;)
      int m_fd;
      std::string m_descriptive_name; 

   };
}




#endif // _MSPP_PAD_HPP_
