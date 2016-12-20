//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Position;
out vec3 FragCoords;


uniform mat4 vikr_View;
uniform mat4 vikr_Model;
uniform mat4 vikr_Projection;

void main() {
  gl_Position = vikr_Projection * vikr_View * vikr_Model * vec4(position, 1.0f);
  TexCoords = tex_coords;
   Normal = mat3(transpose(inverse(vikr_Model))) * normal;
   Position = position;
   FragCoords = vec3(vikr_Model * vec4(position, 1.0f));
}