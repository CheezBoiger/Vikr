//
// Copyright (c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_SHADER_CONFIG_HPP
#define __VIKR_SHADER_CONFIG_HPP



namespace vikr {


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
} // vikr
#endif // __VIKR_SHADER_CONFIG_HPP