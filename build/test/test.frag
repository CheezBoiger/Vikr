#version 430 core

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

out vec4 color;

//uniform sampler2D tex;
uniform vec3 view_pos;
uniform vec3 obj_color;
uniform vec3 light_pos;
uniform vec3 light_color;

void main() {
   //color = vec4(texture(tex, TexCoords));
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
  
  color = vec4(result, 1.0f); 
}