#version 430 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoords;

layout (location = 0) out vec2 TexCoord;
layout (location = 1) out vec3 Normal;


layout (binding = 0) uniform ViewProjection {
  mat4 projection;
  mat4 view;
} vpn;


layout (binding = 1) uniform Model {
  mat4 model;
} mdl;


void main() {
  gl_Position = vpn.projection * vpn.view * mdl.model * vec4(position, 1.0f);
  
}