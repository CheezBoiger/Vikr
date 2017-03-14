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
#include <vikr/graphics/render_device.hpp>
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



/// Material defines the textures, samplers, and descriptor
/// sets to bind to graphic pipelines. this is ultimately 
/// created by the RenderDevice, so create them sparingly.
/// NOTE(): Vulkan can only use uniform buffers, no standalone 
///         uniforms should be implemented in glsl code.
///         Need to redesign Material so that it adheres to vulkan.
class Material : public RenderDeviceObject {
  static const std::string kDefaultName;
public:
  Material(GraphicsAPIType type);

  virtual ~Material() { }

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