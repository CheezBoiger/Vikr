#version 430 core

#include "test.glsl"

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;
in vec3 FragCoords;

out vec4 color;


struct PointLight {
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


//uniform sampler2D texas;
uniform vec3 vikr_CamPosition;
uniform vec3 obj_specular;
uniform vec3 obj_diffuse;
uniform bool blinn;

uniform vec3 light_pos;
uniform vec3 light_ambient;
uniform vec3 light_diffuse;
uniform vec3 light_specular;
uniform float constant;
uniform float linear;
uniform float quadratic;


//uniform sampler2D vikr_TexAlbedo;
//uniform sampler2D vikr_TexNormal;
//uniform sampler2D vikr_TexSpecular;
//uniform sampler2D vikr_TexRoughness;
//uniform sampler2D vikr_TexAmbient;


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 frag_coord, vec3 view_dir) {
  /* Blinn-Phong Implementation! */ 
  // diffuse
  vec3 light_dir = normalize(light.position - frag_coord);
  float distance = length(light.position - frag_coord);
  float diff = max(dot(light_dir, normal), 0.0f);
  // Specular
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = 0.0f;
  if (blinn) {
    vec3 halfway_dir = normalize(light_dir + view_dir);
    spec = pow(max(dot(normal, halfway_dir), 0.0f), 32.0f);
  } else {
    vec3 reflect_dir = reflect(-light_dir, normal);
    spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32.0f) ;
  }
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   
  vec3 ambient = light.ambient * obj_diffuse;
  vec3 diffuse = light.diffuse * diff * obj_diffuse;
  vec3 specular = light_diffuse * spec * obj_specular; // assuming a bright white color. Can be substituted with light_color
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular); 
}


void main() {
  vec3 norm = normalize(Normal);
  vec3 view_dir = normalize(vikr_CamPosition - FragCoords);
  vec3 result = vec3(0.0f);
  PointLight light;
  light.position = light_pos;
  light.constant = constant;
  light.linear = linear;
  light.quadratic = quadratic;
  light.ambient = light_ambient;
  light.diffuse = light_diffuse;
  light.specular = light_specular;
  result = CalculatePointLight(light, norm, FragCoords, view_dir);
  color = vec4(result, 1.0f); 
  //color = vec4(texture(texas, TexCoords));
  //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}