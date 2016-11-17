#version 430 core


// We can consider ambient if need be.
struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};


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
  float cut_off;
};