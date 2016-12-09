//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MATERIAL_HPP
#define __VIKR_MATERIAL_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <shader/shader_config.hpp>
#include <graphics/blendmode.hpp>
#include <graphics/cullmode.hpp>
#include <graphics/depthmode.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <map>

namespace vikr {


class Shader;
struct Uniform;
struct VertexAttrib;
class Texture;



/**
  Material defines the textures, cull, and blend of the Mesh.
*/
class Material {
  static const std::string kDefaultName;
public:
  Material();
  Material(Shader *shader, std::string name);
  Material(Shader *shader);
  Shader *GetShader() { return m_shader; }
  vvoid SetShader(Shader * shader) { m_shader = shader; }

  std::string GetName() { return m_name; }


  GraphicsPipeline GetPipeline() { return pipeline; }
  /**
    Sets the texture for a sampler in the shader.
  */
  vvoid SetTexture(std::string name, Texture *texture, vuint32 i);
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
  
  std::map<std::string, TextureSampler> *GetUniformSamplers() { return &m_uniform_samplers; }
  std::map<std::string, MaterialValue> *GetMaterialValues() { return &m_material_values; } 

protected:

  std::string m_name;
  Shader *m_shader; // weak ref
  /**
    Current Render Pipeline. 
  */
  GraphicsPipeline pipeline;
  /**
    Keep track of the uniforms and samplers of the shader. These values get called by the renderer
    to render textures and materials.
  */
  std::map<std::string, TextureSampler> m_uniform_samplers;
  std::map<std::string, MaterialValue> m_material_values;
}; 
} // vikr
#endif // __VIKR_MATERIAL_HPP