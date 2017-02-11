//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VERT_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 Normal;
  vec3 Tangent;
  vec3 Bitangent;
  vec3 Color;
} vs_out;

uniform mat4 vikr_Model;
uniform mat4 vikr_View;
uniform mat4 vikr_Projection;

void main() {
  vec4 worldPosition = vikr_Model * vec4(position, 1.0f);
  vs_out.FragPos = worldPosition.xyz;
  gl_Position = vikr_Projection * vikr_View * worldPosition;
  vs_out.TexCoords = texCoords;
  
  mat3 normalMat = transpose(inverse(mat3(vikr_Model)));
  vec3 T = normalize(vec3(vikr_Model * vec4(tangent, 0.0f)));
  vec3 B = normalize(vec3(vikr_Model * vec4(bitangent, 0.0f)));
  vec3 N = normalize(vec3(vikr_Model * vec4(normal, 0.0)));
  T = normalize(T - dot(T, N) * N);
  vs_out.Tangent = T;
  vs_out.Normal = N;
  vs_out.Bitangent = B;
}