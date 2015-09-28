#ifndef MATERIAL_MANAGER_INCLUDED_616D14F2_715B_4F86_ABDE_B6B557B24781
#define MATERIAL_MANAGER_INCLUDED_616D14F2_715B_4F86_ABDE_B6B557B24781


#include <core/entity/entity.hpp>
#include <string>


namespace Detail {


class Material_manager
{
public:

  explicit        Material_manager();
  
  void            add(const Core::Entity e, const std::string &filename);
  void            remove(const Core::Entity e);

}; // class


} // ns


#endif // inc guard