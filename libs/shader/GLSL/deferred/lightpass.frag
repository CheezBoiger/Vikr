//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core

in vec2 TexCoords;
in mat3 TBN;

uniform sampler2DMS gPosition;
uniform sampler2DMS gNormal;
uniform sampler2DMS gAlbedo;
uniform sampler2DMS gSpecular;
uniform sampler2DMS gAmbient;
uniform sampler2DMS gTangent;
uniform sampler2DMS gBitangent;
uniform sampler2DMS gNorm;
uniform sampler2DMS gColor;


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
  bool enabled;
};


/**
  Directional Light test.
*/
struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  bool enabled;
};


#define MAX_POINTLIGHTS 2
#define MAX_DIRECTIONALLIGHTS 1

uniform vec3 vikr_CamPosition;

uniform DirectionalLight vikr_directionalLights[MAX_DIRECTIONALLIGHTS];
uniform PointLight vikr_pointLights[MAX_POINTLIGHTS];


vec3 CalculateDirectionalLight(DirectionalLight light, vec3 Normal, 
  vec3 frag_coord, vec3 view_dir, vec4 Diffuse, vec4 Specular, vec4 Ambient, mat3 TBN) 
{
  light.direction = TBN * light.direction;
  vec3 light_dir = normalize(-light.direction);
  float diff = max(dot(light_dir, Normal), 0.0f);
  // Specular work.
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(Normal, halfway_dir), 0.0f), 32.0f);
  vec3 ambient = light.ambient * vec3(Diffuse);
  vec3 diffuse = light.diffuse * diff * vec3(Diffuse);
  vec3 specular = light.specular * spec;
  return (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 Normal, vec3 FragPos, 
  vec3 view_dir, vec4 Diffuse, vec4 Specular, vec4 Ambient, mat3 TBN) 
{
  vec3 TangentLightPos = TBN * light.position;
  /* Blinn-Phong Implementation! */ 
  // diffuse
  vec3 light_dir = normalize(TangentLightPos - FragPos);
  float distance = length(TangentLightPos - FragPos);
  float diff = max(dot(light_dir, Normal), 0.0f);
  float spec = 0.0f;
  vec3 halfway_dir = normalize(light_dir + view_dir);
  spec = pow(max(dot(Normal, halfway_dir), 0.0f), 16.0f);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  vec3 ambient = light.ambient * vec3(Diffuse);
  vec3 diffuse = light.diffuse * diff * vec3(Diffuse);
  vec3 specular =  light.specular * spec * vec3(Specular);
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular);
}



void main() {
  vec4 result = vec4(0.0f);
  for (int sampledIndex = 0; sampledIndex < 8; ++sampledIndex) {
    vec3 FragPos = texelFetch(gPosition, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
    vec4 Diffuse = texelFetch(gAlbedo, ivec2(gl_FragCoord.xy), sampledIndex);
    vec4 Specular = texelFetch(gSpecular, ivec2(gl_FragCoord.xy), sampledIndex);
    vec4 Ambient = texelFetch(gAmbient, ivec2(gl_FragCoord.xy), sampledIndex);
    vec3 Normal = texelFetch(gNormal, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
  
    vec3 Norm = texelFetch(gNorm, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
    vec3 Tangent = texelFetch(gTangent, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
    vec3 Bitangent = texelFetch(gBitangent, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
  
    mat3 TBN = transpose(mat3(Tangent, Bitangent, Norm));
  
    Normal = normalize(Normal * 2.0 - 1.0); // tangent space normal map
  
    vec3 ViewDir = TBN * normalize(vikr_CamPosition - FragPos);
    vec3 TangentFragPos = TBN * FragPos;
  
    //result = Diffuse * 0.01;
  
    for (int i = 0; i < MAX_DIRECTIONALLIGHTS; ++i) {
      if ( vikr_directionalLights[i].enabled) {
        //result += vec4(CalculateDirectionalLight(vikr_directionalLights[i], Normal, 
        //  TangentFragPos, ViewDir, Diffuse, Specular, Ambient, TBN), 0.0f);
      }
    }
    for (int i = 0; i < MAX_POINTLIGHTS; ++i) {
      if (vikr_pointLights[i].enabled) {
        result += vec4(CalculatePointLight(vikr_pointLights[i], Normal, TangentFragPos,
          ViewDir, Diffuse, Specular, Ambient, TBN), 0.0f);
      }
    }
    //result = vec4(pow(result.rgb, vec3(1.0/2.2)), 1.0f);
    gl_FragColor = result; 
  }
  //result = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  
  //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}