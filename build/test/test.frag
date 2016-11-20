#version 430 core

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D tex;

void main() {
  color = vec4(texture(tex, TexCoords));
}