//
// Copyright (c) Mario Garcia, Under the MIT License.
//
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

#define MAX_LIGHTS 2

uniform PointLight vikr_pointLights[MAX_LIGHTS];

uniform sampler2D vikr_TexAlbedo;
uniform sampler2D vikr_TexNormal;
uniform sampler2D vikr_TexSpecular;
uniform sampler2D vikr_TexRoughness;
uniform sampler2D vikr_TexAmbient;


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
    spec = pow(max(dot(normal, halfway_dir), 0.0f), 8.0f);
  } else {
    vec3 reflect_dir = reflect(-light_dir, normal);
    spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 8.0f) ;
  }
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   
  vec3 ambient = light.ambient * vec3(texture(vikr_TexAmbient, TexCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(vikr_TexAlbedo, TexCoords));
  vec3 specular = light.specular * spec * vec3(texture(vikr_TexSpecular, TexCoords)); // assuming a bright white color. Can be substituted with light_color
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular);
}


void main() {
  vec3 norm = normalize(Normal);
  vec3 view_dir = normalize(vikr_CamPosition - FragCoords);
  vec3 result = vec3(0.0f);
  for (int i = 0; i < MAX_LIGHTS; ++i) {
    result += CalculatePointLight(vikr_pointLights[i], norm, FragCoords, view_dir);
  }
  color = vec4(result, 1.0f); 
  //color = vec4(texture(vikr_TexAlbedo, TexCoords));
  //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}