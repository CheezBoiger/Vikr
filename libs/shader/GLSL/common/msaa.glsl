#ifndef __VIKR_MSAA_GLSL
#define __VIKR_MSAA_GLSL


uniform int samples;

vec4 textureMultisample(sampler2DMS sampler, vec2 pos) {
  vec4 color = vec4(0.0);
  for (int i = 0; i < samples; ++i) {
  
  }
}

#endif // __VIKR_MSAA_GLSL