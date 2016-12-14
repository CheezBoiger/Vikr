#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;


struct PointLight {
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};


#define MAX_LIGHTS 2

uniform PointLight vikr_pointLights[MAX_LIGHTS];
uniform vec3 vikr_CamPosition;


vec3 CalculatePointLight(PointLight light, vec3 Normal, vec3 frag_coord, vec3 view_dir, vec3 Diffuse, float Specular) {
  /* Blinn-Phong Implementation! */ 
  // diffuse
  vec3 light_dir = normalize(light.position - frag_coord);
  float distance = length(light.position - frag_coord);
  float diff = max(dot(light_dir, Normal), 0.0f);
  float spec = 0.0f;
  vec3 halfway_dir = normalize(light_dir + view_dir);
  spec = pow(max(dot(Normal, halfway_dir), 0.0f), 8.0f);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   
  vec3 ambient = light.ambient * Diffuse;
  vec3 diffuse = light.diffuse * diff * Diffuse;
  vec3 specular = light.specular * spec * Specular;
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular);
}



void main() {
  vec3 FragPos = texture(gPosition, TexCoords).rgb;
  vec3 Normal = texture(gNormal, TexCoords).rgb;
  vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
  float Specular = texture(gAlbedoSpec, TexCoords).a;
  vec3 view_dir = normalize(vikr_CamPosition - FragPos);
  
  vec3 result = Diffuse;
  
  for (int i = 0; i < MAX_LIGHTS; ++i) {
    result += CalculatePointLight(vikr_pointLights[i], Normal, FragPos, view_dir, Diffuse, Specular);
  }
  
  FragColor = vec4(result, 1.0f);
  //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}