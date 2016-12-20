//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 vikr_Model;
uniform mat4 vikr_View;
uniform mat4 vikr_Projection;

void main() {
  vec4 worldPosition = vikr_Model * vec4(position, 1.0f);
  FragPos = worldPosition.xyz;
  gl_Position = vikr_Projection * vikr_View * worldPosition;
  TexCoords = texCoords;
  
  mat3 normalMat = transpose(inverse(mat3(vikr_Model)));
  Normal = normalMat * normal;
}