#ifndef _PIPELINE_HPP_
#define _PIPELINE_HPP_

#include <string>
#include <vector>
#include <map>
#include <variant>
#include <atomic>

#include <Section.hpp>
#include <nlohmann/json.hpp>

#include <nng/nng.h>
#include <nng/protocol/pipeline0/push.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

namespace mspp {
class Pipeline {
   public:
      Pipeline( const std::string &description ) :
         m_description{ description },
         m_connected{false},
         m_running{false}
      { }

      virtual void connect( ) = 0;
      virtual void start( ) = 0;
      virtual void stop( ) = 0;
      
      // Pull a work-item from the pipeline.
      // Format/encoding specified in the string:
      //  "format=std::string"  (default)
      //  "format=JSON"
      //  "format=XML"
      //  "encode=UTF-8"
      //  "encode=UTF-32", etc.
      virtual std::string pull( const std::string &format ) = 0;
     
      // This is useful for pulling binary messages -- msgpack,
      //  Google Protocol Buffers, Google FlatBuffers, 
      virtual std::vector<std::byte> pull( ) = 0;

      // Push a work-item into the pipeline.
      // Format/encoding of the data:
      //  "format=std::string"  (default)
      //  "format=JSON"
      //  "format=XML"
      //  "encode=UTF-8"
      //  "encode=UTF-32", etc.
      virtual bool push( const std::string &format, const std::string &payload ) = 0;

      // This is useful for pushing binary messages -- msgpack,
      //  Google Protocol Buffers, Google FlatBuffers, 
      virtual bool push( const std::vector<std::byte> &payload ) = 0;


      virtual void add_source( std::unique_ptr< Section > &&section );
      virtual void add_section( std::unique_ptr< Section > &&section  );
      virtual void add_sink( std::unique_ptr< Section > &&section );
   protected:
      //
      // MEMBERS
      // 
      std::string m_description;        // most likely the PID of the process that created this pipeline...
      std::atomic_bool m_connected;
      std::atomic_bool m_running;
     
      // There should really ever only be ONE source-section...
      //   * Use "std::vector::begin" iterator!
      // There should really ever only be ONE sink-section...
      //   * Use "std::vector::end" iterator! 
      std::vector< std::unique_ptr< Section > > m_sections;

   private:
};

}

#endif // _PIPELINE_HPP_
