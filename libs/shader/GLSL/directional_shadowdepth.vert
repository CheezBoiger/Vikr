#version 430 core
layout (location = 0) in vec3 position;

uniform mat4 lightSpaceMatrix;
uniform mat4 vikr_Model;

void main() {
  gl_Position = lightSpaceMatrix * vikr_Model * vec4(position, 1.0f);
}