//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_CONTEXT_HPP
#define __VIKR_GL4_CONTEXT_HPP


#include <graphics/render_context.hpp>


namespace vikr {


class GL4RenderContext : public RenderContext {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4RenderContext);
  GL4RenderContext();

  vvoid Draw(vuint32 vertices) override;
  vvoid DrawIndexed(vuint32 indices, vuint32 vertices) override;
  vvoid SetTexture(Texture *texture, vuint32 index) override;
  vvoid SetRenderTarget(RenderTarget *target, vuint32 index) override;
  vvoid SetRenderPass(RenderPass *pass) override;
  vvoid SetBlendEq(BlendEq eq) override;
  vvoid SetBlendMode(BlendFunc src, BlendFunc dst) override;
  vvoid SetDepthFunc(vuint32 depth) override;
  vvoid EnableCullMode(vbool enable) override;
  vvoid EnableBlendMode(vbool enable) override;
  vvoid EnableDepthMode(vbool enable) override;
  vvoid SetCullFace(CullFace face) override;
  vvoid SetFrontFace(FrontFace face) override;
  vvoid Clear() override;
  vvoid ClearWithColor(glm::vec4 color) override;
  vvoid ChangeViewport(Viewport *port) override;
  vvoid ChangeTopology(Topology topology) override;

private:
  Topology m_currTopology     = VIKR_TRIANGLES;
  CullFace m_currCullFace     = CullFace::vikr_BACK_FACE;
  FrontFace m_currFrontFace   = FrontFace::vikr_COUNTER_CLOCKWISE;
  
};
} // vikr
#endif // __VIKR_GL4_CONTEXT_HPP