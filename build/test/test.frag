#version 430 core

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

out vec4 color;

void main() {
  color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}