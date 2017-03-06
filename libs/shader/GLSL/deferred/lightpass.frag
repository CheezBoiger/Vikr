//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
out vec4 FragColor;
in vec2 TexCoords;
in mat3 TBN;

uniform sampler2DMS gPosition;
uniform sampler2DMS gNormal;
uniform sampler2DMS gAlbedo;
uniform sampler2DMS gSpecular;
uniform sampler2DMS gShadowMap;
uniform sampler2DMS gTangent;
uniform sampler2DMS gBitangent;
uniform sampler2DMS gNorm;
uniform sampler2DMS gColor;
uniform sampler2DMS depthMap;


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
  vec3 position;
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


float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightPos, vec3 Normal, 
    vec3 FragPos, int sampleIndex) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texelFetch(depthMap, ivec2(projCoords.xy), sampleIndex).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // Check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(depthMap);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texelFetch(depthMap, ivec2(projCoords.xy + vec2(x, y) * texelSize), sampleIndex).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
  return shadow;
}


vec3 CalculateDirectionalLight(DirectionalLight light, vec3 Normal, 
  vec3 frag_coord, vec3 view_dir, vec4 Diffuse, vec4 Specular, mat3 TBN,
  vec4 FragPosLightSpace, int sampleIndex) 
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
  float shadow = 0.0f;//ShadowCalculation(FragPosLightSpace, light.position, Normal, frag_coord, sampleIndex);
  return (ambient + (1.0f - shadow) * (diffuse + specular)) * Diffuse.rgb;
}


vec3 CalculatePointLight(PointLight light, vec3 Normal, vec3 FragPos, 
  vec3 view_dir, vec4 Diffuse, vec4 Specular, mat3 TBN) 
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
  float depthValue = 0.0f;
  for (int sampledIndex = 0; sampledIndex < 4; ++sampledIndex) {
    vec3 FragPos = texelFetch(gPosition, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
    vec4 Diffuse = texelFetch(gAlbedo, ivec2(gl_FragCoord.xy), sampledIndex);
    vec4 Specular = texelFetch(gSpecular, ivec2(gl_FragCoord.xy), sampledIndex);
    vec4 ShadowMap = texelFetch(gShadowMap, ivec2(gl_FragCoord.xy), sampledIndex);
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
      if (vikr_directionalLights[i].enabled) {
        result += vec4(CalculateDirectionalLight(vikr_directionalLights[i], Normal, 
          TangentFragPos, ViewDir, Diffuse, Specular, TBN, ShadowMap, sampledIndex), 0.0f);
      }
    }
    for (int i = 0; i < MAX_POINTLIGHTS; ++i) {
      if (vikr_pointLights[i].enabled) {
        result += vec4(CalculatePointLight(vikr_pointLights[i], Normal, TangentFragPos,
          ViewDir, Diffuse, Specular, TBN), 0.0f);
      }
    }
    result = vec4(pow(result.rgb, vec3(1.0/1.1)), 1.0f);
    //depthValue = ShadowMap.r;
    FragColor = result;//vec4(vec3(depthValue), 1.0);
  } 
  //gl_FragColor = texelFetch(shadowMap, ivec2(gl_FragCoord.xy), 0);
  //result = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}