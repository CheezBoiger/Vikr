//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvs;


out VS_OUT {
  vec3 Normal;
  vec3 Position;
  vec2 UVs;
} vs_out;

uniform mat4 vikr_Model;
uniform mat4 vikr_View;
uniform mat4 vikr_Projection;

void main() {
  gl_Position = vikr_Projection * vikr_View * vikr_Model * vec4(position, 1.0f);
  vs_out.Position = vec3(model * vec4(position, 1.0f));
  vs_out.Normal = normal;
  vs_out.UVs = uvs;
}