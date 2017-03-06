//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SHADOW_MAP_HPP
#define __VIKR_SHADOW_MAP_HPP


#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/shader/shader_program.hpp>
#include <vikr/lighting/directional_light.hpp>
#include <vikr/shader/shader.hpp>

#include <vikr/graphics/command_buffer.hpp>

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>


namespace vikr {



class RenderDevice;
class ResourceManager;
class Framebuffer;
class RenderPass;

/**
  ShadowMap implementation.
*/
class DirectionalShadowMap {
public:

  DirectionalShadowMap() { }

  vvoid Init(RenderDevice *device, ResourceManager *mgr);

  
  vvoid Execute(DirectionalLight *light, CommandbufferList *list);


  RenderPass *GetRenderPass() { return m_shadowmapRenderPass; }
  

private:

  ShaderProgram *m_shadowProgram;
  RenderPass *m_shadowmapRenderPass;
  Framebuffer *m_shadowmapFbo;
  RenderDevice *m_device;
};
} // vikr
#endif // __VIKR_SHADOW_MAP_HPP