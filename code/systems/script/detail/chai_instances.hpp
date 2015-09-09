#ifndef CHAI_INSTANCES_INCLUDED_ACEBD83F_9602_4A3F_A0A8_83EE760251C0
#define CHAI_INSTANCES_INCLUDED_ACEBD83F_9602_4A3F_A0A8_83EE760251C0


#include <systems/script/detail/script_fwd.hpp>
#include <chaiscript/ChaiScript.hpp>
#include <stdint.h>


namespace Script_detail {
namespace Chai_instances {


class Chai_instance
{

                  Chai_instance(const Chai_instance&) = delete;
  Chai_instance&  operator=(const Chai_instance&) = delete;

public:

  explicit        Chai_instance(chaiscript::ChaiScript *chai);
                  ~Chai_instance();
                  Chai_instance(Chai_instance&& other);
  Chai_instance&  operator=(Chai_instance&& other);
  
  inline chaiscript::ChaiScript*  get()       { return m_chai; }
  inline void                     flush()     { m_chai = nullptr; } //!< This will not attempt to return the instance.
  inline bool                     is_valid()  { return m_chai != nullptr; }
  
private:

  void _return();
  void _move(Chai_instance &other);

private:

  chaiscript::ChaiScript *m_chai = nullptr;
  
}; // class


void                initialize(const uint32_t number_of_instances);
Chai_instance       get_instance();
bool                return_instance(Chai_instance &instance);


} // ns
} // ns


#endif // include guard