//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coords;


out VERT_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} vs_out;


uniform mat4 vikr_Projection;
uniform mat4 vikr_Model;
uniform mat4 vikr_View;

uniform bool reverse_normals;

void main() {
  gl_Position = vikr_Projection * vikr_View * vikr_Model * vec4(position, 1.0f);
  vs_out.FragPos = vec3(vikr_Model * vec4(position, 1.0f));
  if (reverse_normals) {
    vs_out.Normal = transpose(inverse(mat3(vikr_Model))) * (-1.0f * normal);
  } else {
    vs_out.Normal = transpose(inverse(mat3(vikr_Model))) * normal;
  }
  vs_out.TexCoords = tex_coords;
}