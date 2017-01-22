//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SHADER_HPP
#define __VIKR_SHADER_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <glm/glm.hpp>
#include <string>

namespace vikr {


/**
  Shader type language.
*/
enum ShaderType {
  vikr_GLSL,
  vikr_HLSL,
  vikr_SPIRV
};


/**
  Defined Shader stages.
*/
enum ShaderStage {
  VERTEX_SHADER,
  FRAGMENT_SHADER,
  GEOMETRY_SHADER,
  COMPUTE_SHADER,
  TESSELATION_SHADER
};


/**
  For now it only works with OpenGL, Spir-V not yet implemented!
*/
class Shader {
public:
  Shader();
  Shader(Shader &&shader) = default;
  Shader &operator=(Shader &&shader) = default;
  virtual ~Shader() { }

  virtual vvoid Compile(std::string vs, std::string fs, std::string gs = "") = 0;
  vvoid SetIncludeSearchPath(std::string path) { include_searchpath = path; }
  virtual vvoid Use() = 0;
  virtual vvoid Cleanup() = 0;
  vuint32 GetProgramId() { return shader_id; }
  vbool IsLinked() { return is_linked; }

  ShaderType GetShaderType() { return shader_type; }

  vvoid SetName(std::string name) { shader_name = name; }
  std::string GetName() { return shader_name; }

  vuint32 GetFragId() { return frag_id; }
  vuint32 GetVertId() { return vert_id; }
  vuint32 GetGeomId() { return geom_id; }
  vuint32 GetCompId() { return comp_id; }
  vuint32 GetHullId() { return hull_id; }

protected:

  ShaderType shader_type                = vikr_GLSL;
  std::string include_searchpath        = ".";
  std::string shader_name               = "noname";

  vuint32 shader_id                     = 0;
  vuint32 vert_id                       = 0;
  vuint32 frag_id                       = 0;
  vuint32 geom_id                       = 0;

  // OpenGL 4.3 and up.
  vuint32 comp_id                       = 0;
  vuint32 hull_id                       = 0;
  vbool is_linked;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Shader);
};
} // vikr
#endif // __VIKR_SHADER_HPP