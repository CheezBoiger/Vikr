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
  vikr_WRAP_REPEAT,
  vikr_WRAP_MIRRORED_REPEAT,
  vikr_WRAP_CLAMP_TO_EDGE,
  vikr_WRAP_CLAMP_TO_BORDER
};


/**
Filter mode, depending on distance from the view.
*/
enum TextureFilterMode {
  vikr_FILTER_NEAREST,
  vikr_FILTER_LINEAR,
  vikr_FILTER_NEAREST_MIPMAP_NEAREST,
  vikr_FILTER_LINEAR_MIPMAP_NEAREST,
  vikr_FILTER_LINEAR_MIPMAP_LINEAR,
  vikr_FILTER_NEAREST_MIPMAP_LINEAR
};


/**
Texture type, or target, for the
Texture object.
*/
enum TextureTarget {
  vikr_TARGET_1D,
  vikr_TARGET_2D,
  vikr_TARGET_2D_MULTISAMPLE,
  vikr_TARGET_3D,
  vikr_TARGET_CUBEMAP,
  vikr_TARGET_CUBEMAP_POSITIVE_X,
  vikr_TARGET_CUBEMAP_NEGATIVE_X,
  vikr_TARGET_CUBEMAP_POSITIVE_Y,
  vikr_TARGET_CUBEMAP_NEGATIVE_Y,
  vikr_TARGET_CUBEMAP_POSITIVE_Z,
  vikr_TARGET_CUBEMAP_NEGATIVE_Z
};


enum TextureFormat {
  vikr_FORMAT_RGB,
  vikr_FORMAT_RGBA,
  vikr_FORMAT_RGB16F,
  vikr_FORMAT_RGB32F,
  vikr_FORMAT_DEPTH,
  vikr_FORMAT_ALPHA,
  vikr_FORMAT_RED,
};


/**
    DATA TYPE FORMAT NOT NEEDED. USE TEXTURE FORMAT TO DETERMINE 
    DATA TYPE PRECISION. MODERN RENDERING APIS USE THIS INSTEAD...
*/
enum DataTypeFormat {
  vikr_DATATYPE_UNSIGNED_BYTE,
  vikr_DATATYPE_UNSIGNED_INT,
  vikr_DATATYPE_FLOAT
};
};
#endif // __VIKR_TEXTURE_CONFIG_HPP