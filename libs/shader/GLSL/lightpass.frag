//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gSpecular;
uniform sampler2D gAmbient;


/**
  Point light test.
*/
struct PointLight {
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


/**
  Directional Light test.
*/
struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


#define MAX_POINTLIGHTS 2
#define MAX_DIRECTIONALLIGHTS 1

uniform DirectionalLight vikr_directionalLights[MAX_DIRECTIONALLIGHTS];
uniform PointLight vikr_pointLights[MAX_POINTLIGHTS];
uniform vec3 vikr_CamPosition;
uniform bool gamma;


vec3 CalculateDirectionalLight(DirectionalLight light, vec3 Normal, 
  vec3 frag_coord, vec3 view_dir, vec4 Diffuse, vec4 Specular, vec4 Ambient) 
{
  vec3 light_dir = normalize(-light.direction);
  float diff = max(dot(light_dir, Normal), 0.0f);
  // Specular work.
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(Normal, halfway_dir), 0.0f), 32.0f);
  vec3 ambient = light.ambient * vec3(Ambient);
  vec3 diffuse = light.diffuse * diff * vec3(Diffuse);
  vec3 specular = light.specular * spec * vec3(Specular);
  return (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 Normal, vec3 frag_coord, 
  vec3 view_dir, vec4 Diffuse, vec4 Specular, vec4 Ambient) 
{
  /* Blinn-Phong Implementation! */ 
  // diffuse
  vec3 light_dir = normalize(light.position - frag_coord);
  float distance = length(light.position - frag_coord);
  float diff = max(dot(light_dir, Normal), 0.0f);
  float spec = 0.0f;
  vec3 halfway_dir = normalize(light_dir + view_dir);
  spec = pow(max(dot(Normal, halfway_dir), 0.0f), 32.0f);
  float attenuation = 1.0f / (distance * distance);//(light.constant + light.linear * distance + light.quadratic * (distance * distance));
   
  vec3 ambient = light.ambient * vec3(Ambient);
  vec3 diffuse = light.diffuse * diff * vec3(Diffuse);
  vec3 specular = light.specular * spec * vec3(Specular);
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular);
}



void main() {
  vec3 FragPos = texture(gPosition, TexCoords).rgb;
  vec3 Normal = texture(gNormal, TexCoords).rgb;
  vec4 Diffuse = texture(gAlbedo, TexCoords);
  vec4 Specular = texture(gSpecular, TexCoords);
  vec4 Ambient = texture(gAmbient, TexCoords);
  vec3 view_dir = normalize(vikr_CamPosition - FragPos);
  
  
  vec4 result = vec4(0.0f);
  
  for (int i = 0; i < MAX_DIRECTIONALLIGHTS; ++i) {
    //result += CalculateDirectionalLight(vikr_directionalLights[i], Normal, FragPos, view_dir, Diffuse, Specular, Ambient);
  }
  for (int i = 0; i < MAX_POINTLIGHTS; ++i) {
    result += CalculatePointLight(vikr_pointLights[i], Normal, FragPos, view_dir, Diffuse, Specular, Ambient);
  }
  result = vec4(pow(result.rgb, vec3(1.0/2.2)), result.a);
  FragColor = vec4(result);
  //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}