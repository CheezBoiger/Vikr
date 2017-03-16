//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#version 430 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec4 gSpecular;
layout (location = 4) out vec3 gTangent;
layout (location = 5) out vec3 gBitangent;
layout (location = 6) out vec3 gNorm;

layout (binding = 0) uniform sampler2D vikr_TexAlbedo;
layout (binding = 1) uniform sampler2D vikr_TexNormal;
layout (binding = 2) uniform sampler2D vikr_TexSpecular;
layout (binding = 3) uniform sampler2D vikr_TexRoughness;
layout (binding = 4) uniform sampler2D vikr_TexAmbient;



in VERT_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 Normal;
  vec3 Tangent;
  vec3 Bitangent;
} vs_in;


void main() {

  gPosition = vs_in.FragPos;
  gNormal =  texture(vikr_TexNormal, vs_in.TexCoords);
  gAlbedo = texture(vikr_TexAlbedo, vs_in.TexCoords);
  gSpecular = texture(vikr_TexSpecular, vs_in.TexCoords);
  gTangent = vs_in.Tangent;
  gBitangent = vs_in.Bitangent;
  gNorm = vs_in.Normal;
}