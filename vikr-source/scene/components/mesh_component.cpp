//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <scene/components/mesh_component.hpp>
#include <scene/scene_node.hpp>
#include <renderer/command/mesh_command.hpp>


namespace vikr {


MeshComponent::MeshComponent()
  : SceneComponent(vikr_COMPONENT_MESH)
{
}


vvoid MeshComponent::Update() {
  cmd.m_mesh = mesh;
}
} // vikr