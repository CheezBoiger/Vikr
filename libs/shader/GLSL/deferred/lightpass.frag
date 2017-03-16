//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec2 TexCoords;
layout (location = 0) out vec4 FragColor;

// Uniform gbuffer object.
layout (binding = 0) uniform sampler2DMS gPosition;
layout (binding = 1) uniform sampler2DMS gNormal;
layout (binding = 2) uniform sampler2DMS gAlbedo;
layout (binding = 3) uniform sampler2DMS gSpecular;
layout (binding = 4) uniform sampler2DMS gTangent;
layout (binding = 5) uniform sampler2DMS gBitangent;
layout (binding = 6) uniform sampler2DMS gNorm;
layout (binding = 7) uniform sampler2D Shadowmap;


/// Point light.
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


// Directional Light.
struct DirectionalLight {
  mat4 lightSpaceMatrix;
  vec3 direction;
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  bool enabled;
};


#define MAX_POINTLIGHTS 2
#define MAX_DIRECTIONALLIGHTS 1

// Light information.
layout (binding = 1) uniform LightInformation {
  DirectionalLight vikr_directionalLights[MAX_DIRECTIONALLIGHTS];
  PointLight vikr_pointLights[MAX_POINTLIGHTS];
} lightinfo;


// Camera uniform buffer.
layout (binding = 2) unform Camera {
  vec3 cameraPosition;
} camera;


float LinearizeDepth(float m_depth) {
  float z = m_depth * 2.0 - 1.0;
  return (2.0 * 0.1 * 1000) / (1000 + 0.1 - z * (1000 - 0.1));
}


float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightPos, vec3 Normal, 
    vec3 FragPos, int sampleIndex) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(Shadowmap, projCoords.xy).r;//texelFetch(Shadowmap, ivec2(projCoords.xy), sampleIndex).r; 
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
    vec2 texelSize = 1.0 / textureSize(Shadowmap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(Shadowmap, projCoords.xy + vec2(x, y) * texelSize).r;//texelFetch(Shadowmap, ivec2(projCoords.xy + vec2(x, y) * texelSize), sampleIndex).r; 
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
  vec3 FragPos, vec3 view_dir, vec4 Diffuse, vec4 Specular, int sampleIndex) 
{
  vec3 light_dir = normalize(-light.direction);
  float diff = max(dot(light_dir, Normal), 0.0f);
  // Specular work.
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(Normal, halfway_dir), 0.0f), 32.0f);
  vec3 ambient = light.ambient * vec3(Diffuse);
  vec3 diffuse = light.diffuse * diff * vec3(Diffuse);
  vec3 specular = light.specular * spec;
  float shadow = ShadowCalculation(light.lightSpaceMatrix * vec4(FragPos, 1.0f), light.position, Normal, FragPos, sampleIndex);
  return (ambient + (1.0f - shadow) * (diffuse + specular)) * vec3(Diffuse);
}


vec3 CalculatePointLight(PointLight light, vec3 Normal, vec3 FragPos, 
  vec3 ViewDir, vec4 Diffuse, vec4 Specular) 
{
  /* Blinn-Phong Implementation! */ 
  // diffuse
  vec3 light_dir = normalize(light.position - FragPos);
  float distance = length(light.position - FragPos);
  float diff = max(dot(light_dir, Normal), 0.0f);
  float spec = 0.0f;
  vec3 halfway_dir = normalize(light_dir + ViewDir);
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
    vec3 Normal = texelFetch(gNormal, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
  
    vec3 Norm = texelFetch(gNorm, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
    vec3 Tangent = texelFetch(gTangent, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
    vec3 Bitangent = texelFetch(gBitangent, ivec2(gl_FragCoord.xy), sampledIndex).rgb;
  
    mat3 TBN = transpose(mat3(Tangent, Bitangent, Norm));
  
    Normal = normalize(Normal * 2.0 - 1.0); // tangent space normal map
    vec3 TangentViewPos = TBN * vikr_CamPosition;
    vec3 TangentFragPos = TBN * FragPos;
  
    vec3 ViewDir = normalize(vikr_CamPosition - FragPos);
    vec3 TangentViewDir = normalize(TangentViewPos - TangentFragPos);
    //result = Diffuse * 0.01;
  
    for (int i = 0; i < MAX_DIRECTIONALLIGHTS; ++i) {
      if (vikr_directionalLights[i].enabled) {
        DirectionalLight light = vikr_directionalLights[i];
        light.position = TBN * light.position;
        light.direction = TBN * light.direction;
        result += vec4(CalculateDirectionalLight(light, Normal, 
          TangentFragPos, TangentViewDir, Diffuse, Specular, sampledIndex), 0.0f);
      }
    }
    for (int i = 0; i < MAX_POINTLIGHTS; ++i) {
      if (vikr_pointLights[i].enabled) {
        PointLight light = vikr_pointLights[i];
        light.position = TBN * light.position;
        result += vec4(CalculatePointLight(light, Normal, TangentFragPos,
          TangentViewDir, Diffuse, Specular), 0.0f);
      }
    }
    result = vec4(pow(result.rgb, vec3(1.0/1.1)), 1.0f);
    depthValue = texture(Shadowmap, TexCoords).r;//texelFetch(Shadowmap, ivec2(gl_FragCoord.xy), sampledIndex).r;
    FragColor = result;//vec4(vec3(depthValue), 1.0);
  } 
  //gl_FragColor = texelFetch(shadowMap, ivec2(gl_FragCoord.xy), 0);
  //result = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}