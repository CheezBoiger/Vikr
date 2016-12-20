//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
out vec4 FragColor;


// Input from Vertex shader.
in VERT_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} vs_in;


uniform sampler2D diffuseTex;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float farPlane;
uniform bool shadows;


// Calculate the Shadow.
float ShadowCalc(vec3 fragPos) {
  vec3 fragToLight = fragPos - lightPos;
  float closestDepth = texture(depthMap, fragToLight).r;
  closestDepth *= farPlane;
  float currentDepth = length(fragToLight);
  float bias = 0.05f;
  float shadow = (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
  return shadow;
}


void main() {
  vec3 color = texture(diffuseTex, vs_in.TexCoords).rgb;
  vec3 normal = normalize(vs_in.Normal);
  vec3 lightColor = vec3(0.3f);
  vec3 lightDir = normalize(lightPos - vs_in.FragPos);
  
  // Calculate with Blinn Phong shading. Shadow variable manipulates
  // lighting.
  float diff = max(dot(lightDir, normal), 0.0f);
  vec3 viewDir = normalize(viewPos - vs_in.FragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = 0.0f;
  spec = pow(max(dot(normal, halfwayDir), 0.0f), 64.0);
    vec3 ambient = 0.3 * color;
  vec3 diffuse = diff * lightColor;
  vec3 specular = spec * lightColor;
  float shadow = shadows ? ShadowCalc(vs_in.FragPos) : 0.0f;
  vec3 result = (ambient + (1.0f - shadow) * (diffuse + specular)) * color;
  FragColor = vec4(result, 1.0f);
}