//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MATERIAL_HPP
#define __VIKR_MATERIAL_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/cullmode.hpp>
#include <renderer/blendmode.hpp>
#include <renderer/depthmode.hpp>
#include <shader/shader_config.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace vikr {


class Shader;
struct Uniform;
struct VertexAttrib;
class Texture;


/**
  Sets the Texture samplers into the Material
*/
struct TextureSamplers {
  ShaderUniformType type;
  Texture *texture;
  vuint32 i;
};


/**
  Material defines the textures, cull, and blend of the Mesh.
*/
class Material {
  static const std::string kDefaultName;
public:
  Material(Shader *shader, std::string name);
  Material(Shader *shader);
  Shader *GetShader() { return m_shader; }

  vvoid SetFrontFace(FrontFace mode) { m_frontface = mode; }
  vvoid SetCullFace(CullFace face) { m_cullface = face; }
  vvoid SetIsBlending(vbool blend) { is_blending = blend; }
  vvoid SetBlendDst(BlendFunc funct) { m_blend_dst = funct; }
  vvoid SetBlendSrc(BlendFunc funct) { m_blend_src = funct; }  
  vvoid SetName(std::string name) { m_name = name; }

  vbool IsBlending() { return is_blending; }
  vbool IsCulling() { return is_culling; }
  vbool HasDepth() { return has_depth; }

  CullFace GetCullFace() { return m_cullface; }
  FrontFace GetFrontFace() { return m_frontface; }
  DepthFunc GetDepthFunc() { return m_depth_func; }

  BlendFunc GetBlendSrc() { return m_blend_src; }
  BlendFunc GetBlendDst() { return m_blend_dst; }

  std::string GetName() { return m_name; }

  /**
    Sets the texture for a sampler in the shader.
  */
  vvoid SetTexture(Texture *texture, vuint32 i);
  /**
    Primitive uniform defines.
  */
  vvoid SetInt(std::string name, vint32 value);
  vvoid SetBool(std::string name, vbool value);
  vvoid SetVector4fv(std::string name, glm::vec4 value);
  vvoid SetVector3fv(std::string name, glm::vec3 value);
  vvoid SetVector2fv(std::string name, glm::vec2 value);
  vvoid SetFloat(std::string name, vreal32 value);
  vvoid SetDouble(std::string name, vreal64 value);
  vvoid SetMat4(std::string name, glm::mat4 value);
  vvoid SetMat3(std::string name, glm::mat3 value);
  vvoid SetMat2(std::string name, glm::mat2 value);
  
  std::vector<TextureSamplers> *GetUniformSamplers();
  std::vector<Uniform> *GetUniforms();

protected:

  std::string m_name;
  Shader *m_shader; // weak ref

  vbool has_depth;
  DepthFunc m_depth_func;

  vbool is_culling;
  FrontFace m_frontface;
  CullFace m_cullface;

  vbool is_blending;
  BlendFunc m_blend_src;
  BlendFunc m_blend_dst;
  BlendEq m_blend_equation;
  
  /**
    Keep track of the uniforms and samplers of the shader.
  */
  std::vector<TextureSamplers> m_uniform_samplers;
  std::vector<Uniform> m_uniforms;
}; 
} // vikr
#endif // __VIKR_MATERIAL_HPP