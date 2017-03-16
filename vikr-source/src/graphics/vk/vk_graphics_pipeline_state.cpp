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
    default: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
  }
}


VkCompareOp GetNativeDepthFunc(DepthCompare func) {
  switch (func) {
    case DepthCompare::vikr_DEPTH_LESS: return VK_COMPARE_OP_LESS;
    case DepthCompare::vikr_DEPTH_EQUAL: return VK_COMPARE_OP_EQUAL;
    case DepthCompare::vikr_DEPTH_GEQUAL: return VK_COMPARE_OP_GREATER_OR_EQUAL;
    case DepthCompare::vikr_DEPTH_GREATER: return VK_COMPARE_OP_GREATER;
    case DepthCompare::vikr_DEPTH_LEQUAL: return VK_COMPARE_OP_LESS_OR_EQUAL;
    case DepthCompare::vikr_DEPTH_NEVER: return VK_COMPARE_OP_NEVER;
    case DepthCompare::vikr_DEPTH_NOTEQUAL: return VK_COMPARE_OP_NOT_EQUAL;
    default: return VK_COMPARE_OP_LESS;
  }
}


VkBlendFactor GetNativeBlendFactor(BlendFactor func)
{
  switch (func) {
    case BlendFactor::vikr_BLEND_ZERO: return VK_BLEND_FACTOR_ZERO;
    case BlendFactor::vikr_BLEND_SRC_COLOR: return VK_BLEND_FACTOR_SRC_COLOR;
    case BlendFactor::vikr_BLEND_SRC_ALPHA: return VK_BLEND_FACTOR_SRC_ALPHA;
    case BlendFactor::vikr_BLEND_ONE_MINUS_SRC_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
    case BlendFactor::vikr_BLEND_ONE_MINUS_SRC_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    case BlendFactor::vikr_BLEND_ONE_MINUS_DST_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
    case BlendFactor::vikr_BLEND_ONE_MINUS_DST_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
    case BlendFactor::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
    case BlendFactor::vikr_BLEND_ONE: return VK_BLEND_FACTOR_ONE;
    case BlendFactor::vikr_BLEND_ONE_MINUS_CONSTANT_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
    case BlendFactor::vikr_BLEND_DST_COLOR: return VK_BLEND_FACTOR_DST_COLOR;
    case BlendFactor::vikr_BLEND_DST_ALPHA: return VK_BLEND_FACTOR_DST_ALPHA;
    case BlendFactor::vikr_BLEND_CONSTANT_COLOR: return VK_BLEND_FACTOR_CONSTANT_COLOR;
    case BlendFactor::vikr_BLEND_CONSTANT_ALPHA: return VK_BLEND_FACTOR_CONSTANT_ALPHA;
    default: return VK_BLEND_FACTOR_ONE;
  }
}


VkBlendOp GetNativeBlendOperation(BlendEq eq)
{
  switch (eq) {
    case BlendEq::vikr_BLEND_ADD: return VK_BLEND_OP_ADD;
    case BlendEq::vikr_BLEND_REVERSE_SUBTRACT: return VK_BLEND_OP_REVERSE_SUBTRACT;
    case BlendEq::vikr_BLEND_SUBTRACT: return VK_BLEND_OP_SUBTRACT;
    default: return VK_BLEND_OP_ADD;
  }
}


VkViewport GetNativeViewport(Viewport &viewport) 
{
  VkViewport native = { };
  native.x = viewport.win_x;
  native.y = viewport.win_y;
  native.width = viewport.win_width;
  native.height = viewport.win_height;
  native.minDepth = 0.0f;
  native.maxDepth = 1.0f;
  return native;
}


VkRect2D GetNativeScissor(Scissor2D &scissor) 
{
  VkRect2D native = { };
  native.offset.x = scissor.offsetx;
  native.offset.y = scissor.offsety;
  native.extent.width = scissor.width;  
  native.extent.height = scissor.height;
  return native;
}


VkPolygonMode GetNativePolygonMode(PolygonMode mode) 
{
  switch(mode) {
    case vikr_POLYGON_MODE_FILL: return VK_POLYGON_MODE_FILL;
    case vikr_POLYGON_MODE_LINES: return VK_POLYGON_MODE_LINE;
    case vikr_POLYGON_MODE_POINT: return VK_POLYGON_MODE_POINT;
    default: return VK_POLYGON_MODE_FILL;
  }
}


VKGraphicsPipelineState::VKGraphicsPipelineState()
  : GraphicsPipelineState(vikr_API_VULKAN)
{
}


vvoid VKGraphicsPipelineState::Bake(GraphicsPipelineDescription &description)
{
  if (!device) {
    return;
  }
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
  input_assembly_info.topology = GetNativeTopology(description.topology);
  input_assembly_info.primitiveRestartEnable = VK_FALSE;

  // Set up Viewport Create
  VkPipelineViewportStateCreateInfo viewportstate_info;
  viewportstate_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportstate_info.viewportCount = 1;
  viewportstate_info.pViewports = &GetNativeViewport(description.viewport);
  viewportstate_info.scissorCount = 1;
  viewportstate_info.pScissors = &GetNativeScissor(description.scissor);

  VkPipelineTessellationStateCreateInfo tesselation_info;
  tesselation_info.patchControlPoints = 3;
  tesselation_info.flags = 0;
  tesselation_info.pNext = nullptr;
  
  // Set up Rasterizer State
  VkPipelineRasterizationStateCreateInfo rasterizer_info;
  rasterizer_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer_info.depthClampEnable = VK_FALSE;
  rasterizer_info.rasterizerDiscardEnable = VK_FALSE;
  rasterizer_info.polygonMode = GetNativePolygonMode(description.polygon); // We will use a debugger to handle this.
  rasterizer_info.lineWidth = 1.0f;
  rasterizer_info.cullMode = GetNativeCullMode(description.cull);
  rasterizer_info.frontFace = GetNativeFrontFace(description.front);
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
  depthstencil_info.depthCompareOp = GetNativeDepthFunc(description.dcompare);
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
  colorblend_attachment.srcColorBlendFactor = GetNativeBlendFactor(description.bsrc); 
  // Equations needed from Pipelinestate
  colorblend_attachment.dstColorBlendFactor = GetNativeBlendFactor(description.bdst);
  colorblend_attachment.colorBlendOp = GetNativeBlendOperation(description.beq);
  colorblend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  colorblend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  colorblend_attachment.alphaBlendOp = GetNativeBlendOperation(description.beq);

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

  VkPipelineDynamicStateCreateInfo dynamicstate_info = { };
  // none yet.

  // Graphics pipeline info.
  VkGraphicsPipelineCreateInfo graphics_pipeline_info = { };
  graphics_pipeline_info.pVertexInputState = &vertex_input_info;
  graphics_pipeline_info.pInputAssemblyState = &input_assembly_info;
  graphics_pipeline_info.pMultisampleState = &multisample_info;
  graphics_pipeline_info.pRasterizationState = &rasterizer_info;
}
} // vikr