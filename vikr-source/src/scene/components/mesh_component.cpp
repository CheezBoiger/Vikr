//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/scene/components/mesh_component.hpp>
#include <vikr/scene/scene_node.hpp>
#include <vikr/renderer/command/mesh_command.hpp>


namespace vikr {


MeshComponent::MeshComponent()
  : SceneComponent(vikr_COMPONENT_MESH)
{
}


vvoid MeshComponent::Update() {
  cmd.m_mesh = mesh;
}
} // vikr