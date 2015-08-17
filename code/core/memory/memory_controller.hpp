#ifndef MEMORY_CONTROLLER_INCLUDED_FAC31692_7222_41E0_BA06_D8DE31AFF9F9
#define MEMORY_CONTROLLER_INCLUDED_FAC31692_7222_41E0_BA06_D8DE31AFF9F9


#include <stdint.h>
#include <cstdlib>
#include <core/memory/memory_chunk.hpp>


namespace Core {
namespace Memory {


bool              initialize(const std::size_t size_of_pre_allocation);
Memory_chunk      request_block(const std::size_t reserve_size);
std::size_t       memory_pool_remaining();


}
} // namespace


#endif // include guards