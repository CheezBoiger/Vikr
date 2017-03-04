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


enum ImageFormat {
  // Garaunteed to be within Vulkan devices.
  vikr_FORMAT_R8_SINT,
  vikr_FORMAT_R8_UINT,
  vikr_FORMAT_R8_UNORM,
  vikr_FORMAT_R8_SNORM,
  vikr_FORMAT_R16_SFLOAT,
  vikr_FORMAT_R16_SINT,
  vikr_FORMAT_R16_UINT,
  vikr_FORMAT_R32_SFLOAT,
  vikr_FORMAT_R32_SINT,
  vikr_FORMAT_R32_UINT,
  vikr_FORMAT_R8G8B8A8_SINT,
  vikr_FORMAT_R8G8B8A8_UINT,
  vikr_FORMAT_R8G8B8A8_UNORM,
  vikr_FORMAT_R8G8B8A8_SNORM,
  vikr_FORMAT_R8G8B8A8_SRGB,
  vikr_FORMAT_R16G16B16A16_SFLOAT,
  vikr_FORMAT_R16G16B16A16_SINT,
  vikr_FORMAT_R16G16B16A16_UINT,
  vikr_FORMAT_R32G32B32A32_SFLOAT,
  vikr_FORMAT_R32G32B32A32_SINT,
  vikr_FORMAT_R32G32B32A32_UINT,
  // depth components.
  vikr_FORMAT_D16_UNORM,
  vikr_FORMAT_D32_SFLOAT,

  // 50% or less, availability on vulkan devices.
  vikr_FORMAT_R8G8B8_SINT,
  vikr_FORMAT_R8G8B8_UINT,
  vikr_FORMAT_R16G16B16_SFLOAT, 
  vikr_FORMAT_R16G16B16_SINT,
  vikr_FORMAT_R16G16B16_UINT,
  vikr_FORMAT_R32G32B32_SFLOAT,
  vikr_FORMAT_R32G32B32_SINT,
  vikr_FORMAT_R32G32B32_UINT,
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