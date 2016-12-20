//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MATERIAL_GLSL
#define __VIKR_MATERIAL_GLSL


// We can consider ambient if need be.
struct VikrMaterial {
  sampler2D vikr_TexAmbient;
  sampler2D vikr_TexSpecular;
  sampler2D vikr_TexAlbedo;
  sampler2D vikr_TexNormal;
  sampler2D vikr_TexRoughness;
};

#endif // __VIKR_MATERIAL_GLSL