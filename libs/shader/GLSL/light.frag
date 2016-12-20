//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core

out vec4 color;

in vec3 Position;
in vec3 Normal;
in vec3 TexCoords;

uniform vec3 light_color;

void main() {
  color = vec4(light_color, 1.0f);
}