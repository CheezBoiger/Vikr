//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;

out VERT_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 Normal;
  vec3 Tangent;
  vec3 Bitangent;
} vs_out;

uniform mat4 vikr_Model;
uniform mat4 vikr_View;
uniform mat4 vikr_Projection;


void main() {
  vec4 worldPosition = vikr_Model * vec4(position, 1.0f);
  vs_out.FragPos = worldPosition.xyz;
  gl_Position = vikr_Projection * vikr_View * worldPosition;
  vs_out.TexCoords = texCoords;
  
  mat3 nMatrix = transpose(inverse(mat3(vikr_Model)));
  vec3 T = normalize(nMatrix * tangent);
  vec3 N = normalize(nMatrix * normal);
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);
  vs_out.Tangent = T;
  vs_out.Normal = N;
  vs_out.Bitangent = B;
}