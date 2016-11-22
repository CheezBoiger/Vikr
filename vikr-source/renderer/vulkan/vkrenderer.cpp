//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <renderer/vulkan/vkrenderer.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


VKRenderer::VKRenderer()
  : Renderer(vikr_VULKAN)
{
}


vint32 VKRenderer::Init() {
  VikrLog::DisplayMessage(VIKR_ERROR, "Not Implemented!");
  return false;
}

vvoid VKRenderer::Render() {
  VikrLog::DisplayMessage(VIKR_ERROR, "Not Implemented!");
}
} // vikr