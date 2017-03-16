#version 430 core
#extension GL_ARB_separate_shader_objects : enable

in VERT_OUT {
  vec3 TexCoords;
} vert_in;


uniform (binding = 0) samplerCube skybox;


void main() {
  gl_FragColor = texture(skybox, vert_in.TexCoords);
}