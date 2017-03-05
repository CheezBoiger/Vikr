//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec4 gSpecular;
layout (location = 4) out vec4 gAmbient;
layout (location = 5) out vec3 gTangent;
layout (location = 6) out vec3 gBitangent;
layout (location = 7) out vec3 gNorm;

uniform sampler2D vikr_TexAlbedo;
uniform sampler2D vikr_TexNormal;
uniform sampler2D vikr_TexSpecular;
uniform sampler2D vikr_TexRoughness;
uniform sampler2D vikr_TexAmbient;


uniform int vikr_Mask;


in VERT_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 Normal;
  vec3 Tangent;
  vec3 Bitangent;
  vec3 Color;
} vs_in;


void main() {

  gPosition = vs_in.FragPos;
  gNormal =  texture(vikr_TexNormal, vs_in.TexCoords);
  gAlbedo = texture(vikr_TexAlbedo, vs_in.TexCoords);
  gSpecular = texture(vikr_TexSpecular, vs_in.TexCoords);
  gAmbient = texture(vikr_TexAmbient, vs_in.TexCoords);
  gTangent = vs_in.Tangent;
  gBitangent = vs_in.Bitangent;
  gNorm = vs_in.Normal;
}