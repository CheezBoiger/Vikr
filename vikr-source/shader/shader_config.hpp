//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_SHADER_CONFIG_HPP
#define __VIKR_SHADER_CONFIG_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <glm/glm.hpp>


namespace vikr {


class Texture;


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