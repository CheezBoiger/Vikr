#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Position;
out vec3 FragCoords;


uniform mat4 vikr_view;
uniform mat4 vikr_model;
uniform mat4 vikr_projection;

void main() {
  gl_Position = vikr_projection * vikr_view * vikr_model * vec4(position, 1.0f);
  TexCoords = tex_coords;
   Normal = mat3(transpose(inverse(vikr_model))) * normal;
   Position = position;
   FragCoords = vec3(vikr_model * vec4(position, 1.0f));
}