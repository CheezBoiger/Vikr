//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec4 gSpecular;
layout (location = 4) out vec4 gAmbient;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D vikr_TexAlbedo;
uniform sampler2D vikr_TexNormal;
uniform sampler2D vikr_TexSpecular;
uniform sampler2D vikr_TexRoughness;
uniform sampler2D vikr_TexAmbient;

void main() {
  gPosition = FragPos;
  gNormal = normalize(Normal);
  gAlbedo = texture(vikr_TexAlbedo, TexCoords);
  gSpecular = texture(vikr_TexSpecular, TexCoords);
  gAmbient = texture(vikr_TexAmbient, TexCoords);
}