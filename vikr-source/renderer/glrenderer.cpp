#include <renderer/glrenderer.hpp>
#include <renderer/renderer.hpp>

namespace vikr {


GLRenderer::GLRenderer()
  : Renderer(vikr_OPENGL)
{
}

vint32 GLRenderer::Init() {
  return true;
}
} // vikr