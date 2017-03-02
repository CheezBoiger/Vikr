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
class Cubemap;


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
  vikr_VERTEX_SHADER,
  // Fragment shader is equivalent to Pixel shaders.
  vikr_FRAGMENT_SHADER,
  vikr_GEOMETRY_SHADER,
  vikr_COMPUTE_SHADER,
  // Tesselation Control shader is equivalent to Hull shaders.
  vikr_TESS_CONTROL_SHADER,
  // Tesselation Evaluation shader is equivalent to Domain shaders.
  vikr_TESS_EVALUATION_SHADER,
  // Pixel Shader is equivalent to Fragment shaders.
  vikr_PIXEL_SHADER = vikr_FRAGMENT_SHADER,
  // Hull shader is equivalent to Control shaders.
  vikr_HULL_SHADER = vikr_TESS_CONTROL_SHADER,
  // Domain shader is equivalent to evaluation shaders.
  vikr_DOMAIN_SHADER = vikr_TESS_EVALUATION_SHADER
};


/**
We determine the uniform type for our Uniform object
within the shader.
*/
enum ShaderUniformType {
  vikr_UNIFORM_TEXTURE2D,
  vikr_UNIFORM_TEXTURE3D,
  vikr_UNIFORM_SAMPLER2D,
  vikr_UNIFORM_SAMPLER3D,
  vikr_UNIFORM_SAMPLERCUBE,
  vikr_UNIFORM_INT,
  vikr_UNIFORM_FLOAT,
  vikr_UNIFORM_DOUBLE,
  vikr_UNIFORM_BOOL,
  vikr_UNIFORM_VEC2,
  vikr_UNIFORM_VEC3,
  vikr_UNIFORM_VEC4,
  vikr_UNIFORM_MAT2,
  vikr_UNIFORM_MAT3,
  vikr_UNIFORM_MAT4
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
  ShaderUniformType   type;
  union { 
    Texture           *texture;
    Cubemap           *cubemap;
  };
  vuint32             i;
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