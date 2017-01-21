//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE_HPP
#define __VIKR_TEXTURE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/stb/stb_image.h>
#include <vikr/shader/texture_config.hpp>
#include <string>

namespace vikr {


/**
  Texture object, abstraction. This is the texture that is associated with 
  Materials, Meshes, RenderTargets, Cubemaps, and SceneObjects.
*/
class Texture {
protected:
  static const std::string kDefaultName;
public:
  Texture() { }
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Texture);

  virtual ~Texture() { }
  /**
    Generates bytecode for the provided image.
  */
  static vbyte *CreateImageByteCode(std::string tex_path, 
            vint32 *width, vint32 *height, vint32 *channels, vbool alpha);

  TextureTarget GetTargetFormat() { return m_target; }
  TextureFormat GetFormat() { return m_format; }
  TextureFormat GetInternalFormat() { return m_internal_format; }
  TextureFilterMode GetFilterMin() { return m_filter_min; }
  TextureFilterMode GetFilterMax() {  return m_filter_max; }
  DataTypeFormat GetDataTypeFormat() { return m_datatype; }
  /**
    Texture coordinate wrapping for coord S. 
  */
  TextureWrapMode GetWrapS() { return m_wrap_s; }
  /**
    Texture coordinate wrapping for coord t.
  */
  TextureWrapMode GetWrapT() { return m_wrap_t; }
  /**
    Texture coordinate wrapping for coord r.
  */
  TextureWrapMode GetWrapR() { return m_wrap_r; }
  /**
    Determines if the Texture is mipmapped.
  */
  vbool IsMipmapping() { return m_mipmapping; }

  /**
    Get the width of the texture image.
  */
  vint32 GetWidth() { return m_width; }

  /**
    Get the path to the source image file of this texture.
  */
  std::string GetPath() { return m_path; }

  /**
    Get the name of this texture.
  */
  std::string GetName() { return m_name; }

  /**
    Create the Texture object.
  */
  virtual vint32 Create(vbyte *bytecode) = 0;
  /**
    Bind our texture object with the associated attachment point
    ( or, our id).
  */
  virtual vvoid Bind(vint32 id = -1) = 0;
  /**
    Unbind the texture from our Renderer.
  */
  virtual vvoid Unbind() = 0;

  virtual vvoid SetFormat(TextureFormat format) = 0;
  virtual vvoid SetInternalFormat(TextureFormat format) = 0;
  virtual vvoid SetFilterMin(TextureFilterMode filter) = 0;
  virtual vvoid SetFilterMax(TextureFilterMode filter) = 0;
  /**
    Texture clamp modes. Tells our Rendering API how to clamp the texture onto 
    a Mesh or Quad. This is specified for coord S.
  */
  virtual vvoid SetWrapS(TextureWrapMode mode) = 0;
  /**
    Texture clamp modes. Tells our Rendering API how to clamp the texture onto
    a Mesh or Quad. This is specified for coord T.
  */
  virtual vvoid SetWrapT(TextureWrapMode mode) = 0;
  /**
    Texture clamp modes. Tells our Rendering API how to clamp the texture onto
    a Mesh or Quad. This is specified for coord R.
  */
  virtual vvoid SetWrapR(TextureWrapMode mode) = 0;

  virtual vvoid SetDataTypeFormat(DataTypeFormat format) = 0;

  /**
    Get the native texture id.
  */
  virtual vuint32 GetNativeId() = 0;
  /**
    Set whether this texture needs to generate a mipmap for itself.
  */
  vvoid SetMipmapping(vbool mipmap) { m_mipmapping = mipmap; }
  /**
    Grab the path of the image file that this texture is going to load.
  */
  vvoid SetPath(std::string path) { m_path = path; }
  /**
    Width size of the texture object.
  */
  vvoid SetWidth(vint32 width) { m_width = width; }

  vvoid SetName(std::string name) { m_name = name; }

protected:

  TextureTarget     m_target                    = vikr_TEXTURE_2D;
  TextureFormat     m_format                    = vikr_RGBA;
  TextureFormat     m_internal_format           = vikr_RGBA;
  TextureFilterMode m_filter_min                = vikr_TEXTURE_LINEAR_MIPMAP_LINEAR;
  TextureFilterMode m_filter_max                = vikr_TEXTURE_LINEAR;
  TextureWrapMode   m_wrap_s                    = vikr_TEXTURE_REPEAT;
  TextureWrapMode   m_wrap_t                    = vikr_TEXTURE_REPEAT;
  TextureWrapMode   m_wrap_r                    = vikr_TEXTURE_REPEAT;
  DataTypeFormat    m_datatype                  = data_UNSIGNED_BYTE;
  vbool             m_mipmapping                = true;
  vbool             m_alpha                     = true;
  vuint32           m_width                     = 0;
  std::string       m_path                      = "";
  std::string       m_name                      = "noname";

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP