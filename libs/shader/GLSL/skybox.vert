#version 430 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;


out VERT_OUT {
  vec3 TexCoords;
} vert_out;


uniform mat4 vikr_Projection;
uniform mat4 vikr_View;

void main() {
  vec4 pos = vikr_Projection * vikr_View * vec4(position, 1.0f);
  gl_Position = pos.xyww;
  vert_out.TexCoords = position;
}