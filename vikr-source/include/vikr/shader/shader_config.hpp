//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_SHADER_CONFIG_HPP
#define __VIKR_SHADER_CONFIG_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <glm/glm.hpp>

#include <string>


namespace vikr {


class Texture;


/**
Shader format language.
*/
enum ShaderLanguage {
  vikr_NOLANG,
  vikr_GLSL,
  vikr_HLSL,
  vikr_SPIRV
};


/**
Defined Shader stages.
*/
enum ShaderStage {
  VERTEX_SHADER,
  // Fragment shader is equivalent to Pixel shaders.
  FRAGMENT_SHADER,
  GEOMETRY_SHADER,
  COMPUTE_SHADER,
  // Tesselation Control shader is equivalent to Hull shaders.
  TESS_CONTROL_SHADER,
  // Tesselation Evaluation shader is equivalent to Domain shaders.
  TESS_EVALUATION_SHADER,
  // Pixel Shader is equivalent to Fragment shaders.
  PIXEL_SHADER = FRAGMENT_SHADER,
  // Hull shader is equivalent to Control shaders.
  HULL_SHADER = TESS_CONTROL_SHADER,
  // Domain shader is equivalent to evaluation shaders.
  DOMAIN_SHADER = TESS_EVALUATION_SHADER
};


/**
We determine the uniform type for our Uniform object
within the shader.
*/
enum ShaderUniformType {
  vikr_TEXTURE2D,
  vikr_TEXTURE3D,
  vikr_SAMPLER2D,
  vikr_SAMPLER3D,
  vikr_SAMPLERCUBE,
  vikr_INT,
  vikr_FLOAT,
  vikr_DOUBLE,
  vikr_BOOL,
  vikr_VEC2,
  vikr_VEC3,
  vikr_VEC4,
  vikr_MAT2,
  vikr_MAT3,
  vikr_MAT4
};


/**
Calculated uniforms in GLSL file.
*/
struct Uniform {
  std::string       uniform_name;
  ShaderUniformType uniform_type;
  vint32            uniform_size;
  vuint32           uniform_location;
};


/**
Vertex Attributes.
*/
struct VertexAttrib {
  std::string       attrib_name;
  ShaderUniformType attrib_type;
  vint32            attrib_size;
  vuint32           attrib_location;
};


/**
Sets the Texture samplers into the Material
*/
struct TextureSampler {
  ShaderUniformType type;
  Texture           *texture;
  vuint32           i;
};


/**
Material values that are added to modify the shader.
*/
struct MaterialValue {
  ShaderUniformType type;
  union {
    vbool     m_bool;
    vint32    m_integer;
    vreal32   m_float;
    vreal64   m_double;
    glm::vec2 m_vec2;
    glm::vec3 m_vec3;
    glm::vec4 m_vec4;
    glm::mat2 m_mat2;
    glm::mat3 m_mat3;
    glm::mat4 m_mat4;
  };

  MaterialValue() { }
};
} // vikr
#endif // __VIKR_SHADER_CONFIG_HPP