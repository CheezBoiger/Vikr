//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MATERIAL_HPP
#define __VIKR_MATERIAL_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/shader_config.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/graphics_config.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <map>

namespace vikr {


class ShaderProgram;
struct Uniformbuffer;
struct VertexAttrib;
class Texture;
class Cubemap;



/// Material defines the textures, cull, and blend of the Mesh.
/// NOTE(): Vulkan can only use uniform buffers, no standalone 
///         uniforms should be implemented in glsl code.
///         Need to redesign Material so that it adheres to vulkan.
class Material : public GUID {
  static const std::string kDefaultName;
public:
  Material();

  /// Get the name of this material. The name isn't much of a concern,
  /// It does not hold any unique values.
  std::string GetName() { return m_name; }
  
  /// Set the name of this material.
  vvoid SetName(std::string name) { m_name = name; }

  /// Sets the texture for a sampler in the shader.
  vvoid SetTexture(vuint32 bind, Texture *texture);
  vvoid SetCubemap(vuint32 bind, Cubemap *cubemap);
  vvoid Clear() { m_tex_samplers.clear(); }
  
  std::map<std::string, TextureSampler> *GetUniformSamplers() { return &m_tex_samplers; }

protected:
  std::string m_name;

  /// Keep track of the uniforms and samplers of the shader. These values get called by the renderer
  /// to render textures and materials.
  std::map<std::string, TextureSampler> m_tex_samplers;
}; 
} // vikr
#endif // __VIKR_MATERIAL_HPP