#version 430 core


// We can consider ambient if need be.
struct Material {
  // sampler2D ambient;
  sampler2D diffuse;
  sampler2D specular;
  // sampler2D albedo;
  float shininess;
};