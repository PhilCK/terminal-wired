#include <systems/script/detail/chai_instances.hpp>
#include <utils/directory.hpp>
#include <utils/logging.hpp>
#include <vector>


namespace
{
  std::vector<std::unique_ptr<chaiscript::ChaiScript>> m_chai_instances;
  std::vector<chaiscript::ChaiScript*> m_available_chai;
}


namespace Script_detail {
namespace Chai_instances {


void
initialize(const uint32_t number_of_instances)
{
  m_chai_instances.reserve(number_of_instances);
  
  for(uint32_t i = 0; i < number_of_instances; ++i)
  {
    m_chai_instances.emplace_back(new chaiscript::ChaiScript({util::get_resource_path()}));
  }
  
  m_available_chai.reserve(number_of_instances);
  
  for(const auto &ch : m_chai_instances)
  {
    m_available_chai.emplace_back(ch.get());
  }
}


Chai_instance
get_instance()
{
  assert(!m_available_chai.empty());
  
  // Are there available instances.
  if(m_available_chai.empty())
  {
    return Chai_instance(nullptr);
  }

  auto avail_instance = Chai_instance(m_available_chai.back());
  m_available_chai.erase(m_available_chai.end() - 1);
  
  return avail_instance;
}


bool
return_instance(Chai_instance &instance)
{
  // Some debug checks
  #ifndef NDEBUG
  if(instance.get() == nullptr)
  {
    assert(instance.get());
    util::log_error("Chai_instance - Returning a null chai instance.");
    return false;
  }
  
  bool found = false;
  for(const auto &ch : m_chai_instances)
  {
    if(ch.get() == instance.get())
    {
      found = true;
      break;
    }
  }
  
  if(!found)
  {
    util::log_error("Chai_instance - Returning an instance that we don't have.");
    return false;
  }
  #endif
  
  m_available_chai.push_back(instance.get());
  
  // Null the instance.
  Chai_instance null_instance(nullptr);
  instance.flush();
  
  return true;
}


Chai_instance::Chai_instance(chaiscript::ChaiScript *chai)
: m_chai(chai)
{
}


void
Chai_instance::_return()
{
  if(m_chai)
  {
    return_instance(*this);
    m_chai = nullptr;
  }
}


Chai_instance::~Chai_instance()
{
  _return();
}


void
Chai_instance::_move(Chai_instance &other)
{
  _return();
  
  m_chai = other.m_chai;
  other.m_chai = nullptr;
}


Chai_instance::Chai_instance(Chai_instance&& other)
{
  _move(other);
}


Chai_instance&
Chai_instance::operator=(Chai_instance&& other)
{
  _move(other);
  return *this;
}


} // ns
} // ns