#ifndef ACTOR_INCLUDED_FFB507C8_48D2_449C_BBBB_47F1EDBC3FCC
#define ACTOR_INCLUDED_FFB507C8_48D2_449C_BBBB_47F1EDBC3FCC


#include <core/entity/entity.hpp>
#include <math/mat/mat4.hpp>


namespace Actor {


void        turn_right(const Core::Entity e, const float turn);
void        move_forward(const Core::Entity e, const float fwd);
void        jump(const Core::Entity e, const float jmp);


} // ns


#endif // include guard