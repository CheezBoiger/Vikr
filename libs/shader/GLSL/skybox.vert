#version 430 core
layout (location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 vikr_Projection;
uniform mat4 vikr_View;

void main() {
  vec4 pos = vikr_Projection * vikr_View * vec4(position, 1.0f);
  gl_Position = pos.xyww;
  TexCoords = position;
}