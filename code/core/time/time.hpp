#ifndef TIME_INCLUDED_041D4F47_92CE_45BF_A3EF_783225BF46D0
#define TIME_INCLUDED_041D4F47_92CE_45BF_A3EF_783225BF46D0


namespace Core {
namespace Time {

namespace Detail
{
  void        initialize();
  void        think();
  void        de_initialize();
}

float       get_delta_time();


} // ns
} // ns


#endif // include guard