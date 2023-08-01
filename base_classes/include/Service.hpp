#ifndef _SERVICE_HPP_
#define _SERVICE_HPP_

#include <string>

#include <nlohmann/json.hpp>
#include <Pipeline.hpp>

namespace mspp {

class Service {
   public: 
      Service( ) = delete;
      Service( const std::string &service_name ) : 
         m_service_name{ service_name }
      { };

      void add( Pipeline &pipeline );

      void remove( Pipeline &pipeline );

      // Invoke the "start()" method for all pipelines. The pipelines are int
      // turn to call the "start()" method for their respective sections.
      void start( );

      // By default, this is a simple "while() loop" function that responds
      // to polls from the surveyor pattern in the discovery-agent process.
      void run( );

   private:
      std::string m_service_name;
};

}

#endif // _SERVICE_HPP_
