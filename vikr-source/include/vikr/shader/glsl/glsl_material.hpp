//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_MATERIAL_HPP
#define __VIKR_GLSL_MATERIAL_HPP


#include <vikr/shader/material.hpp>
#include <vikr/shader/glsl/gl4_texture.hpp>
#include <vikr/shader/texture_config.hpp>

#include <map>
#include <string>


namespace vikr {


class GLSLMaterial : public Material {
public:

  vvoid SetTexture(vuint32 bind, Texture *texture) override;
  vvoid SetCubemap(vuint32 bind, Cubemap *cubemap) override;

  Texture *GetTexture(vuint32 bind) override;
  Cubemap *GetCubemap(vuint32 bind) override;
  
  virtual vbool RemoveTexture(vuint32 bind) override;
  virtual vbool RemoveCubemap(vuint32 bind) override;

  std::map<vuint32, TextureSampler> &GetTexSamplers() { return m_tex_samplers; }

private:
  std::map<vuint32, TextureSampler> m_tex_samplers;
};
} // vikr
#endif // __VIKR_GLSL_MATERIAL_HPP