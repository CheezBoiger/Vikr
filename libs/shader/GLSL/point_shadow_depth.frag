//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core

in vec4 FragPos;

uniform vec3 lightpos;
uniform float far_plane;

void main() {
  float light_dist = length(FragPos.xyz - lightpos);
  light_dist = light_dist / far_plane;
  gl_FragDepth = light_dist;
}