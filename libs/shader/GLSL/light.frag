#version 430 core
#include "common/material.glsl"
#include "common/light.glsl"


in VS_OUT {
  vec3 Position;
  vec3 Normal;
  vec3 UVs;
} frag_in;


out vec4 color;

// We will defer the lighting to render the number of lights in 
// the scene in the last pass.
#define MAX_LIGHTS 32

uniform vec3 ViewPos;
uniform Material material;
uniform DirectionalLight dir_light[MAX_LIGHTS];
uniform PointLight point_lights[MAX_LIGHTS];
uniform SpotLight spot_lights[MAX_LIGHTS];


void main() {
  // Algorithm: 
  // 1. Render Directional lights,
  // 2. Render Point lights.
  // 3. Any spotlights we render last.
  color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

