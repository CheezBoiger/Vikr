#version 430 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 tex_coords;

out vec2 TexCoords;


void main() {
  gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
  TexCoords = tex_coords;
}