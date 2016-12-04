#ifndef __VIKR_LIGHT_GLSL
#define __VIKR_LIGHT_GLSL

// Very simple Light struct using colors instead of 
// texture samplers.
struct Light {
  vec3 vikr_Ambient;
  vec3 vikr_Diffuse;
  vec3 vikr_Specular;
};


struct PointLight {
  Light light;
  vec3 vikr_Position;
  
  float vikr_Constant;
  float vikr_Linear;
  float vikr_Quadratic;
};


struct DirectionalLight {
  Light light;
  vec3 vikr_Direction;
};


struct SpotLight {
  Light light;
  vec3 vikr_Position;
  vec3 vikr_Direction;
 
  float vikr_Constant;
  float vikr_Linear;
  float vikr_Quadratic;
  float vikr_Cutoff;
  float vikr_OuterCutoff;
};

#endif // __VIKR_LIGHT_GLSL