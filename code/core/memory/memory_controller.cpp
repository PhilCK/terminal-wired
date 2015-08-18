#include <core/memory/memory_controller.hpp>


namespace
{
  Core::Memory_chunk pre_allocated_memory;
  Core::Memory_chunk available_allocated_memory;
}


namespace Core {
namespace Memory {


bool
initialize(const std::size_t size_of_pre_allocation)
{
  pre_allocated_memory.start_of_chunk = new uint8_t[size_of_pre_allocation];
  pre_allocated_memory.size_of_chunk = size_of_pre_allocation;
  
  available_allocated_memory = pre_allocated_memory;
  
  return true;
}


Memory_chunk
request_block(const std::size_t reserve_size)
{
  return Core::Memory_chunk();
}


std::size_t
memory_pool_remaining()
{
  return 0;
}


} // namespace
} // namespace