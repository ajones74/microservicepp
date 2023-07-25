#ifndef _SERVICE_HPP_
#define _SERVICE_HPP_

#include <nlohmann/json.hpp>
#include <Pipeline.hpp>

namespace mspp {

   using json = nlohmann::json;

class Service {
   public: 
      Service( ) = delete;
      Service( const std::string &service_name,
               Pipeline &logging_pipe,
               Pipeline &config_pipe ) :
         m_service_name{ service_name },
         m_logging_pipeline{ logging_pipe },
         m_config_pipeline{ config_pipe }
      { };

      void set_configuration( const nlohmann::json &config_json );
      void make_pipe( const std::string &pipe_label );
      
      void link_pipes( const std::string &from,
                       const std::string &to );
      void link_pipes( const std::string &from,
                       Pipeline &to);
      void link_pipes( Pipeline &from,
                       Pipeline &to );

      // * Calling this function establishes the ROLE ( client / server )
      //   and PATTERN ( pub/sub, ventilator/worker/sink, push/pull, etc )
      //   for this SERVICE.
      // * Calling the connect() method in a PIPELINE is a complementary
      //   perspective: ROLEs are reversed and the complementary pattern
      //   is used.
      void run( );

   private:
      std::string m_service_name;
      Pipeline m_logging_pipeline;
      Pipeline m_config_pipeline;
};

}

#endif // _SERVICE_HPP_
