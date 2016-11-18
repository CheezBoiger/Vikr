#version 430 core

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