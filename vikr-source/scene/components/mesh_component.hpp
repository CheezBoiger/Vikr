//
// Copright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MESH_COMPONENT_HPP
#define __VIKR_MESH_COMPONENT_HPP


#include <scene/components/scene_component.hpp>
#include <renderer/command/primitive_command.hpp>
#include <mesh/mesh.hpp>


namespace vikr {


class MeshCommand;


class MeshComponent : public SceneComponent {
public:
  MeshComponent();

  vvoid Update() override;

  RenderCommand *GetCommand() override { return &cmd; }

  /**
    Mesh object to reference.
  */
  Mesh *mesh;

private:

  PrimitiveCommand cmd;
};
} // vikr
#endif // __VIKR_MESH_COMPONENT_HPP