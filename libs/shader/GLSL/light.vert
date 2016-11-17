#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uvs;


out VS_OUT {
  vec3 Normal;
  vec3 Position;
  vec2 UVs;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position, 1.0f);
  vs_out.Position = vec3(model * vec4(position, 1.0f));
  vs_out.Normal = mat3(transpose(inverse(model))) * normal; // Not sure if I want this?
  vs_out.UVs = uvs;
}