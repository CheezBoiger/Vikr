//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoords;

uniform mat4 vikr_Model;

void main() {
  gl_Position = vikr_Model * vec4(position, 1.0f);
}