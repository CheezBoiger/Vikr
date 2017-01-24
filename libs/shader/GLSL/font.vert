#version 430
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 projection;

void main() {
  gl_Position = projection * vec4(vertex.xy, 0.0f, 1.0f);
  TexCoords = vertex.zw;
}