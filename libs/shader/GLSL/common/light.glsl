#ifndef __VIKR_LIGHT_GLSL
#define __VIKR_LIGHT_GLSL

// Very simple Light struct using colors instead of 
// texture samplers.
struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


struct PointLight {
  Light light;
  vec3 position;
  
  float constant;
  float linear;
  float quadratic;
};


struct DirectionalLight {
  Light light;
  vec3 direction;
};


struct SpotLight {
  Light light;
  vec3 position;
  vec3 direction;
 
  float constant;
  float linear;
  float quadratic;
  float cutoff;
  float outer_cutoff;
};

#endif // __VIKR_LIGHT_GLSL