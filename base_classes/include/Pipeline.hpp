#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <string>
#include <vector>

#include <Section.hpp>


namespace mspp {

class Pipeline {
   public:
      Pipeline( ) = delete;
      Pipeline( const std::string &pipeline_string );
      void connect( ); 
      std::string pull( const std::string &format );

   private:
      std::string m_pipeline_name;
      std::vector<Section> m_sections;
};

}

#endif // _PIPELINE_HPP_
