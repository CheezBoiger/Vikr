#ifndef __VIKR_MATERIAL_GLSL
#define __VIKR_MATERIAL_GLSL


// We can consider ambient if need be.
struct Material {
  // sampler2D ambient;
  sampler2D diffuse;
  sampler2D specular;
  // sampler2D albedo;
  float shininess;
};

#endif // __VIKR_MATERIAL_GLSL