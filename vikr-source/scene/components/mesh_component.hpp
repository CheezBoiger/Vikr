//
// Copright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MESH_COMPONENT_HPP
#define __VIKR_MESH_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <mesh/mesh.hpp>


namespace vikr {


class MeshCommand;


class MeshComponent : public SceneComponent {
public:
  MeshComponent();

  vvoid Update() override;

  /**
    Mesh object to reference.
  */
  Mesh *mesh;
};
} // vikr
#endif // __VIKR_MESH_COMPONENT_HPP