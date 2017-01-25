#version 430
layout (location = 0) in vec3 vertex;
layout (location = 2) in vec2 uv;

out vec2 TexCoords;

uniform mat4 projection;

void main() {
  gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
  TexCoords = uv;
}