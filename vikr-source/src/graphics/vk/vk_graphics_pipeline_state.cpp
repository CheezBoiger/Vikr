//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/graphics/vk/vk_graphics_pipeline_state.hpp>

namespace vikr {


VkPrimitiveTopology GetNativeTopology(Topology topology) {
  switch (topology) {
    case Topology::VIKR_LINES: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case Topology::VIKR_LINE_STRIP: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case Topology::VIKR_POINTS: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case Topology::VIKR_TRIANGLES: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case Topology::VIKR_TRIANGLE_FAN: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
    case Topology::VIKR_TRIANGLE_STRIP: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    case Topology::VIKR_TRIANGLE_STRIP_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
    default: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  }
}


VkCullModeFlagBits GetNativeCullMode(CullFace mode) {
  switch (mode) {
    case CullFace::vikr_BACK_FACE: return VK_CULL_MODE_BACK_BIT;
    case CullFace::vikr_FRONT_FACE: return VK_CULL_MODE_FRONT_BIT;
    default: return VK_CULL_MODE_BACK_BIT;
  }
}


VkFrontFace GetNativeFrontFace(FrontFace face) {
  switch (face) {
    case FrontFace::vikr_CLOCKWISE: return VK_FRONT_FACE_CLOCKWISE;
    case FrontFace::vikr_COUNTER_CLOCKWISE: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
    default: return VK_FRONT_FACE_CLOCKWISE;
  }
}


VkCompareOp GetNativeDepthFunc(DepthFunc func) {
  switch (func) {
    case DepthFunc::vikr_DEPTH_LESS: return VK_COMPARE_OP_LESS;
    case DepthFunc::vikr_DEPTH_EQUAL: return VK_COMPARE_OP_EQUAL;
    case DepthFunc::vikr_DEPTH_GEQUAL: return VK_COMPARE_OP_GREATER_OR_EQUAL;
    case DepthFunc::vikr_DEPTH_GREATER: return VK_COMPARE_OP_GREATER;
    case DepthFunc::vikr_DEPTH_LEQUAL: return VK_COMPARE_OP_LESS_OR_EQUAL;
    case DepthFunc::vikr_DEPTH_NEVER: return VK_COMPARE_OP_NEVER;
    case DepthFunc::vikr_DEPTH_NOTEQUAL: return VK_COMPARE_OP_NOT_EQUAL;
    default: return VK_COMPARE_OP_LESS;
  }
}


VKGraphicsPipelineState::VKGraphicsPipelineState()
{
  m_viewport.win_x = 0;
  m_viewport.win_y = 0;
  // Must be obtained from the swapchain instead.
  m_viewport.win_width;
  m_viewport.win_height; 
  UpdateNativeViewport();
}


vvoid VKGraphicsPipelineState::UpdateNativeViewport()
{ 
  // Getting more precise, are we?
  m_native_viewport.x = static_cast<float> (m_viewport.win_x);
  m_native_viewport.y = static_cast<float> (m_viewport.win_y);
  
  // Filled with native swapchain width and height.
  m_native_viewport.width;
  m_native_viewport.height;
  // Stick to default/standard depth values [0.0f, 1.0f].
  m_native_viewport.minDepth = 0.0f;
  m_native_viewport.maxDepth = 1.0f;
}


vvoid VKGraphicsPipelineState::Setup()
{
  // Set up Vertex Input.
  VkPipelineVertexInputStateCreateInfo vertex_input_info;
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = 0;
  vertex_input_info.pVertexBindingDescriptions = nullptr;
  vertex_input_info.vertexAttributeDescriptionCount = 0;
  vertex_input_info.pVertexAttributeDescriptions = nullptr;

  // Set up Vertex Assembly
  VkPipelineInputAssemblyStateCreateInfo input_assembly_info;
  input_assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly_info.topology = GetNativeTopology(m_topology);
  input_assembly_info.primitiveRestartEnable = VK_FALSE;

  // Set up Viewport Create
  VkPipelineViewportStateCreateInfo viewportstate_info;
  viewportstate_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportstate_info.viewportCount = 1;
  viewportstate_info.pViewports = &m_native_viewport;
  viewportstate_info.scissorCount = 1;
  viewportstate_info.pScissors = &m_native_scissor;
  
  // Set up Rasterizer State
  VkPipelineRasterizationStateCreateInfo rasterizer_info;
  rasterizer_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer_info.depthClampEnable = VK_FALSE;
  rasterizer_info.rasterizerDiscardEnable = VK_FALSE;
  rasterizer_info.polygonMode = VK_POLYGON_MODE_FILL; // We will use a debugger to handle this.
  rasterizer_info.lineWidth = 1.0f;
  rasterizer_info.cullMode = GetNativeCullMode(m_cullface);
  rasterizer_info.frontFace = GetNativeFrontFace(m_frontface);
  // We may need to adjust these for shadow mapping, but for now just default
  rasterizer_info.depthBiasEnable = VK_FALSE;
  rasterizer_info.depthBiasConstantFactor = 0.0f;
  rasterizer_info.depthBiasClamp = 0.0f;
  rasterizer_info.depthBiasSlopeFactor = 0.0f;

  // Create Multisample State
  VkPipelineMultisampleStateCreateInfo multisample_info;
  multisample_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisample_info.sampleShadingEnable = VK_FALSE;
  multisample_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT; // This can be adusted to increase x msaa
  multisample_info.minSampleShading = 1.0f;
  multisample_info.pSampleMask = nullptr;
  multisample_info.alphaToCoverageEnable = VK_FALSE;  
  multisample_info.alphaToOneEnable = VK_FALSE;

  // Depth-stencil state.
  VkPipelineDepthStencilStateCreateInfo depthstencil_info;
  depthstencil_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depthstencil_info.depthTestEnable = (m_depth ? VK_TRUE : VK_FALSE);
  depthstencil_info.depthWriteEnable = (m_depth ? VK_TRUE : VK_FALSE);
  depthstencil_info.depthCompareOp = GetNativeDepthFunc(m_depthfunc);
  depthstencil_info.depthBoundsTestEnable = VK_FALSE;
  depthstencil_info.minDepthBounds = 0.0f;
  depthstencil_info.maxDepthBounds = 1.0f;
  // for now we will disable stencil components.
  depthstencil_info.stencilTestEnable = VK_FALSE;
  depthstencil_info.back = { }; // < VkStencilOpState info > needed.
  depthstencil_info.front = { }; // same as above

  // Color Blending state
  VkPipelineColorBlendAttachmentState colorblend_attachment;
  colorblend_attachment.colorWriteMask = 
    VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
    VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorblend_attachment.blendEnable = (m_blend ? VK_TRUE : VK_FALSE);  
  colorblend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; 
  // Equations needed from Pipelinestate
  colorblend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  colorblend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
  colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  colorblend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;

  // Color Blend state info.
  VkPipelineColorBlendStateCreateInfo colorblendstate_info;
  colorblendstate_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorblendstate_info.logicOpEnable = VK_FALSE;
  colorblendstate_info.logicOp = VK_LOGIC_OP_COPY;  
  colorblendstate_info.attachmentCount = 1;
  colorblendstate_info.pAttachments = &colorblend_attachment;
  colorblendstate_info.blendConstants[0] = 0.0f;
  colorblendstate_info.blendConstants[1] = 0.0f;
  colorblendstate_info.blendConstants[2] = 0.0f;
  colorblendstate_info.blendConstants[3] = 0.0f;
}
} // vikr