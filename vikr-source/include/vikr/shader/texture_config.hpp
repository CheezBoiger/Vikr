//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE_CONFIG_HPP
#define __VIKR_TEXTURE_CONFIG_HPP



namespace vikr {

/**
Texture wrap mode depending on the
s, t, r texture coordinates.
*/
enum TextureWrapMode {
  vikr_TEXTURE_REPEAT,
  vikr_TEXTURE_MIRRORED_REPEAT,
  vikr_TEXTURE_CLAMP_TO_EDGE,
  vikr_TEXTURE_CLAMP_TO_BORDER
};


/**
Filter mode, depending on distance from the view.
*/
enum TextureFilterMode {
  vikr_TEXTURE_NEAREST,
  vikr_TEXTURE_LINEAR,
  vikr_TEXTURE_NEAREST_MIPMAP_NEAREST,
  vikr_TEXTURE_LINEAR_MIPMAP_NEAREST,
  vikr_TEXTURE_LINEAR_MIPMAP_LINEAR,
  vikr_TEXTURE_NEAREST_MIPMAP_LINEAR
};


/**
Texture type, or target, for the
Texture object.
*/
enum TextureTarget {
  vikr_TEXTURE_1D,
  vikr_TEXTURE_2D,
  vikr_TEXTURE_2D_MULTISAMPLE,
  vikr_TEXTURE_3D,
  vikr_TEXTURE_CUBEMAP,
  vikr_TEXTURE_CUBEMAP_POSITIVE_X,
  vikr_TEXTURE_CUBEMAP_NEGATIVE_X,
  vikr_TEXTURE_CUBEMAP_POSITIVE_Y,
  vikr_TEXTURE_CUBEMAP_NEGATIVE_Y,
  vikr_TEXTURE_CUBEMAP_POSITIVE_Z,
  vikr_TEXTURE_CUBEMAP_NEGATIVE_Z
};


enum TextureFormat {
  vikr_RGB,
  vikr_RGBA,
  vikr_RGB16F,
  vikr_DEPTH,
  vikr_ALPHA,
  vikr_RED
};


enum DataTypeFormat {
  data_UNSIGNED_BYTE,
  data_UNSIGNED_INT,
  data_FLOAT
};
};
#endif // __VIKR_TEXTURE_CONFIG_HPP