//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_DIRECTIONAL_LIGHT_HPP
#define __VIKR_DIRECTIONAL_LIGHT_HPP


#include <vikr/lighting/light.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/shader/shader_program.hpp>


namespace vikr {


class Framebuffer;
class RenderPass;


/**
  Directional light mimicks light at an infinite point. 
  It is not necessarily an inifinite point where light is emitted
  from, but it helps mimick that feelings. Think of sunlight.
*/
class DirectionalLight : public Light {
  static vuint32 directionlight_count;
public:
  DirectionalLight();

  glm::vec3 GetDirection() { return m_direction; }


  vvoid SetNear(vreal32 f) { near_plane = f; }
  vvoid SetFar(vreal32 f) { far_plane = f; }

  vvoid SetPos(glm::vec3 position) override;

  /**
    Updates the light-space matrix to use for shadows.
  */
  vvoid Update() override;

  vvoid Execute(CommandbufferList *bufferlist) override;

  vvoid Init(RenderDevice *device, ShaderProgram *program) override;

  /**
    Get the light space matrix.
  */
  glm::mat4 GetLightSpace() { return m_lightSpaceMatrix; }

  /**
    The Depth map render from the light's perspective.
  */
  Texture *GetDepthMap() { return m_depthTexture; }

protected:
  /**
    Direct that the light is facing.
  */
  glm::vec3 m_direction;

  /**
    view-projection matrix of the directional light.
  */
  glm::mat4 m_lightSpaceMatrix;

  /**
    projection matrix of the light.
  */
  glm::mat4 m_lightProjection;

  /**
    view matrix of the light.
  */
  glm::mat4 m_lightView;

  /**
  */
  vreal32 near_plane;
  vreal32 far_plane;

  Texture *m_depthTexture;
  Framebuffer *m_fbo; 
  RenderPass *m_renderpass;
};
} // vikr
#endif // __VIKR_DIRECTIONAL_LIGHT_HPP