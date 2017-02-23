#version 430 core
in VERT_OUT {
  vec3 TexCoords;
} vert_in;


uniform samplerCube skybox;


void main() {
  gl_FragColor = texture(skybox, vert_in.TexCoords);
}