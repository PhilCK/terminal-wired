#ifndef MEMORY_CHUNK_INCLUDED_35F78FF3_C762_4333_B9CF_F02EBEDEC70D
#define MEMORY_CHUNK_INCLUDED_35F78FF3_C762_4333_B9CF_F02EBEDEC70D


#include <cstdlib>


namespace Core {


struct Memory_chunk
{
  std::size_t   size_of_chunk = 0;
  void*         start_of_chunk = nullptr;
}; // struct


} // namespace


#endif // include guard