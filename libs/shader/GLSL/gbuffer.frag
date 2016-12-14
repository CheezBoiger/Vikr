#version 430 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D vikr_TexAlbedo;
uniform sampler2D vikr_TexSpecular;

void main() {
  gPosition = FragPos;
  gNormal = normalize(Normal);
  gAlbedoSpec.rgb = texture(vikr_TexAlbedo, TexCoords).rgb;
  gAlbedoSpec.a = texture(vikr_TexSpecular, TexCoords).r;
}