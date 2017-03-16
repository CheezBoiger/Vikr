//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_COMMANDBUFFER_HPP
#define __VIKR_VK_COMMANDBUFFER_HPP


#include <vikr/graphics/command_buffer.hpp>

#include <vikr/graphics/vk/vk.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


/// Vulkan Commandbuffer wrapper. This is to abstract the 
/// vkCommandBuffer from the implementation of the renderer.
class VKCommandbuffer : public Commandbuffer {
public:
  VKCommandbuffer()
    : recording(false)
    , Commandbuffer(vikr_API_VULKAN)
  { }

  vvoid BeginRecord() override;
  vvoid EndRecord() override;
  vvoid Draw(vuint32 start, vuint32 vertices, vuint32 instances) override;
  vvoid DrawIndexed(const vvoid *indices, vuint32 vertices, vuint32 instances) override;
  vvoid BindRenderPass(RenderPass *pass) override;
  vvoid UnbindRenderPass() override;
  vvoid Clear() override;
  vvoid ClearWithColor(glm::vec4 color) override;
  vvoid SetViewport(Viewport *viewport) override;
  vvoid SetScissor(Scissor2D *scissor) override;
  vvoid BindGraphicsPipelineState(GraphicsPipelineState *pipelinestate) override;
  vvoid BindComputePipelineState(ComputePipelineState *pipelinestate) override;
  vvoid BindVertexbuffers(Vertexbuffer *buffer) override;
  vvoid BindMaterial(Material *material) override;
   
  void SetBufferData(VertexUsageType type,
    std::unique_ptr<std::vector<Vertex> > data) override;

  vbool IsRecording() override { return recording; }

private:
  vbool recording;
  VkCommandBuffer m_commandbuffer;
};


} // vikr
#endif // __VIKR_VK_COMMANDBUFFER_HPP