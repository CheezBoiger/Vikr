//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE_HPP
#define __VIKR_TEXTURE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vikr/graphics/render_device.hpp>
#include <string>

namespace vikr {


/// Texture object, abstraction. This is the texture that is associated with 
/// Materials, Meshes, RenderTargets, Cubemaps, and SceneObjects.
class Texture : public RenderDeviceObject, public GUID {
protected:
  static const std::string kDefaultName;
public:

  /// Defines a texture 
  static const vuint32 kNoTextureId;
  Texture(GraphicsAPIType type) 
    : RenderDeviceObject(type) { }
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Texture);

  virtual ~Texture();

  /// Generates bytecode for the provided image.
  static vbyte *CreateImageByteCode(std::string filepath, 
            vint32 *width, vint32 *height, vint32 *channels, vbool alpha);

  /// Target format, intends to be the type of format that the texture is going to be.
  /// This can be a 1D, 2D, 3D, or cubemap.
  virtual TextureTarget GetTargetFormat() = 0;
  virtual ImageFormat GetFormat() = 0;
  virtual TextureFilterMode GetFilterMin() = 0;
  virtual TextureFilterMode GetFilterMax() = 0;

  /// Texture coordinate wrapping for coord S. 
  virtual TextureWrapMode GetWrapS() = 0;

  /// Texture coordinate wrapping for coord t.
  virtual TextureWrapMode GetWrapT() = 0;

  /// Texture coordinate wrapping for coord r.
  virtual TextureWrapMode GetWrapR() = 0;

  /// Determines if the Texture is mipmapped.
  virtual vbool IsMipmapping() = 0;

  /// Get the width of the texture image.
  virtual vint32 GetWidth() = 0;

  virtual vint32 GetHeight() = 0;
  virtual vint32 GetDepth() = 0;

  /// Get the path to the source image file of this texture.
  virtual std::string GetPath() = 0;

  /// Get the name of this texture.
  virtual std::string GetName() = 0;

  /// Create the Texture object.
  virtual vint32 Finalize() = 0;

  /// Bind our texture object with the associated attachment point
  /// ( or, our id).
  virtual vvoid Bind(vint32 id = -1) = 0;

  /// Unbind the texture from our Renderer.
  virtual vvoid Unbind() = 0;

  /// Format represents the storage type of the texture. This can be RGB, RGBA, Depth, or
  /// ALPHA, etc.
  virtual vvoid SetFormat(ImageFormat format) = 0;
  virtual vvoid SetFilterMin(TextureFilterMode filter) = 0;
  virtual vvoid SetFilterMax(TextureFilterMode filter) = 0;
  virtual vvoid SetTarget(TextureTarget target) = 0;

  /// Texture clamp modes. Tells our Rendering API how to clamp the texture onto 
  /// a Mesh or Quad. This is specified for coord S.
  virtual vvoid SetWrapS(TextureWrapMode mode) = 0;

  /// Texture clamp modes. Tells our Rendering API how to clamp the texture onto
  /// a Mesh or Quad. This is specified for coord T.
  virtual vvoid SetWrapT(TextureWrapMode mode) = 0;

  /// Texture clamp modes. Tells our Rendering API how to clamp the texture onto
  /// a Mesh or Quad. This is specified for coord R.
  virtual vvoid SetWrapR(TextureWrapMode mode) = 0;
  virtual vbool IsMultisampled() = 0;
  virtual vvoid SetMultisampled(vbool enable) = 0;

  /// Set whether this texture needs to generate a mipmap for itself.
  virtual vvoid SetMipmapping(vbool mipmap) = 0;

  /// Grab the path of the image file that this texture is going to load.
  virtual vvoid SetPath(std::string path) = 0;

  /// Width size of the texture object.
  virtual vvoid SetWidth(vint32 width) = 0;

  virtual vvoid SetHeight(vint32 height) = 0;
  virtual vvoid SetDepth(vint32 depth) = 0;
  virtual vvoid SetName(std::string name) = 0;
  virtual vvoid SetBytecode(vbyte *bytecode, vbool is_stbi = true) = 0;
  virtual vbyte *GetBytecode() = 0;
  virtual vvoid Cleanup() = 0;
  virtual vvoid SetSamples(vint32 samples) = 0;
  virtual vint32 GetSamples() = 0;

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP