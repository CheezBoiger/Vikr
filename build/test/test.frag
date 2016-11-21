#version 430 core

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

out vec4 color;

//uniform sampler2D tex;
uniform vec3 view_pos;
uniform vec3 obj_color;
uniform vec3 light_pos;
//uniform vec3 light_color;
uniform bool blinn;

void main() {
/*   //color = vec4(texture(tex, TexCoords));
  float ambient_strength = 0.1f;
  vec3 ambient = ambient_strength * light_color;
  
  vec3 norm = normalize(Normal);
  vec3 light_dir = normalize(light_pos - Position);
  float diff = max(dot(norm, light_dir), 0.0f);
  vec3 diffuse = diff * light_color;
  
  float specular_strength = 0.5f;
  vec3 view_dir = normalize(view_pos - Position);
  vec3 reflect_dir = reflect(-light_dir, norm);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);
  vec3 specular = specular_strength * spec * light_color;
  
  vec3 result = (ambient + diffuse + specular) * obj_color;
  */
  
  /* Blinn-Phong Implementation! */
  vec3 ambient = 0.05 * obj_color;
  // diffuse
  vec3 light_dir = normalize(light_pos - Position);
  vec3 normal = normalize(Normal);
  float diff = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = diff * obj_color;
  
  // Specular
  vec3 view_dir = normalize(view_pos - Position);
  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = 0.0f;
  if (blinn) {
    vec3 halfway_dir = normalize(light_dir + view_dir);
    spec = pow(max(dot(normal, halfway_dir), 0.0f), 32.0f);
  } else {
    vec3 reflect_dir = reflect(-light_dir, normal);
    spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 8.0f) ;
  }
  vec3 specular = vec3(0.3) * spec; // assuming a bright white color. Can be substituted with light_color
  color = vec4(ambient + diffuse + specular, 1.0f); 
}