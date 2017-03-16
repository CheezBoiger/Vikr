//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_graphics_pipeline_state.hpp>
#include <vikr/graphics/gl4/gl4_device.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>

#include <vikr/shader/glsl/glsl_linker.hpp>

#include <vikr/input/window.hpp>


namespace vikr {


GLenum GetGLBlendMode(BlendFactor func) {
  switch (func) {
    case BlendFactor::vikr_BLEND_CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;  
    case BlendFactor::vikr_BLEND_CONSTANT_COLOR: return GL_CONSTANT_COLOR;
    case BlendFactor::vikr_BLEND_DST_ALPHA: return GL_DST_ALPHA;
    case BlendFactor::vikr_BLEND_DST_COLOR: return GL_DST_COLOR;
    case BlendFactor::vikr_BLEND_ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
    case BlendFactor::vikr_BLEND_ONE: return GL_ONE;
    case BlendFactor::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFactor::vikr_BLEND_ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;  
    case BlendFactor::vikr_BLEND_ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
    case BlendFactor::vikr_BLEND_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFactor::vikr_BLEND_ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
    case BlendFactor::vikr_BLEND_SRC_ALPHA: return GL_SRC_ALPHA;
    case BlendFactor::vikr_BLEND_SRC_COLOR: return GL_SRC_COLOR;
    case BlendFactor::vikr_BLEND_ZERO: return GL_ZERO;
    default: return GL_ONE_MINUS_CONSTANT_ALPHA;
  }
}


GLenum GetGLDepthFunc(DepthCompare mode) {
  switch (mode) {
    case DepthCompare::vikr_DEPTH_ALWAYS: return GL_ALWAYS;
    case DepthCompare::vikr_DEPTH_EQUAL: return GL_EQUAL;
    case DepthCompare::vikr_DEPTH_GEQUAL: return GL_GEQUAL;
    case DepthCompare::vikr_DEPTH_GREATER: return GL_GREATER;
    case DepthCompare::vikr_DEPTH_LEQUAL: return GL_LEQUAL;
    case DepthCompare::vikr_DEPTH_LESS: return GL_LESS;
    case DepthCompare::vikr_DEPTH_NEVER: return GL_NEVER;
    case DepthCompare::vikr_DEPTH_NOTEQUAL: return GL_NOTEQUAL;
    default: return GL_LESS;  
  }
}


GLenum GetGLBlendEq(BlendEq eq) {
  switch (eq) {
    case BlendEq::vikr_BLEND_ADD: return GL_FUNC_ADD;
    case BlendEq::vikr_BLEND_REVERSE_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT;
    case BlendEq::vikr_BLEND_SUBTRACT: return GL_FUNC_SUBTRACT;
    default: return GL_FUNC_ADD;
  }
}


GLenum GetGLCullFace(CullFace face)
{
  switch (face) {
    case CullFace::vikr_BACK_FACE: return GL_BACK;
    case CullFace::vikr_FRONT_FACE: return GL_FRONT;
    case CullFace::vikr_FRONT_AND_BACK: return GL_FRONT_AND_BACK;
    default: return GL_FRONT_AND_BACK;
  }
}


GLenum GetGLTopology(Topology topology) {
  switch (topology) {
    case Topology::VIKR_LINES: return GL_LINES;
    case Topology::VIKR_TRIANGLES: return GL_TRIANGLES;
    case Topology::VIKR_POINTS: return GL_POINTS;
    case Topology::VIKR_TRIANGLE_FAN: return GL_TRIANGLE_FAN;
    case Topology::VIKR_LINE_STRIP: return GL_LINE_STRIP;
    case Topology::VIKR_TRIANGLE_STRIP_ADJACENCY: return GL_TRIANGLE_STRIP_ADJACENCY;
    default: return GL_TRIANGLES;  
  }
}


GLenum GetGLPolygonMode(PolygonMode mode)
{
  switch (mode) {
    case vikr_POLYGON_MODE_FILL: return GL_FILL;
    case vikr_POLYGON_MODE_LINES: return GL_LINES;
    case vikr_POLYGON_MODE_POINT: return GL_POINT;
    default: return GL_FILL;
  }
}


GL4GraphicsPipelineState::GL4GraphicsPipelineState()
  : m_shaderProgram(0)
  , GraphicsPipelineState(vikr_API_OPENGL)
{
}


vvoid GL4GraphicsPipelineState::Bake(GraphicsPipelineDescription &description)
{
  m_cull = description.culling;
  m_depth = description.depth;
  m_blend = description.blend;
  m_blendeq = GetGLBlendEq(description.beq);
  m_blendsrc = GetGLBlendMode(description.bsrc);
  m_blenddst = GetGLBlendMode(description.bdst);
  m_depthCompare = GetGLDepthFunc(description.dcompare);
  m_cullface = GetGLCullFace(description.cull);
  m_frontface = description.front == FrontFace::vikr_COUNTER_CLOCKWISE ? GL_CCW : GL_CW;
  m_topology = GetGLTopology(description.topology);
  m_polygon = GetGLPolygonMode(description.polygon);

  if (description.m_shaders.empty()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Shaders required for this pipeline!");
  }

  GLSLLinker linker;
  // Attach shaders into the shader program.
  shaders.clear();
  for (Shader *shader : description.m_shaders) {
    if (!shader) continue;
    GLSLShader *glShaderObject = static_cast<GLSLShader *>(shader);
    shaders[shader->GetShaderStage()] = glShaderObject;
    if (!glShaderObject->IsCompiled()) {
      VikrLog::DisplayMessage(VIKR_WARNING, "A shader was not compiled. Skipping => " + 
        shader->GetName());
      continue;
    }
    if (!linker.LoadShader(shader)) {
      VikrLog::DisplayMessage(VIKR_WARNING, "Could not load shader => " + 
        shader->GetName() + ". Shader already loaded with similar shader stage.");
    }
  }
  linker.Link();

  if (!linker.IsLinked()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failed to link shaders to program! Aborting...");
    return;  
  }
  
  if (m_shaderProgram > -1) {
    glDeleteProgram(m_shaderProgram);
    m_shaderProgram = -1;
  }
  m_shaderProgram = linker.GetProgramId();

  m_viewport = description.viewport;
  m_scissor = description.scissor;

  // everything in order...
}


GraphicsPipelineState *GL4GraphicsPipelineState::CreateChild(GraphicsPipelineDescription &inherited)
{
  GraphicsPipelineState *pipeline =
    static_cast<GL4RenderDevice *>(GetRenderDevice())->CreateGraphicsPipelineState(true);
  GL4GraphicsPipelineState *gl4pipe = 
    static_cast<GL4GraphicsPipelineState *>(pipeline);
  gl4pipe->m_blend = m_blend;
  gl4pipe->m_blenddst = m_blenddst;
  gl4pipe->m_blendsrc = m_blendsrc;
  gl4pipe->m_blendeq = m_blendeq;
  gl4pipe->m_depth = m_depth;
  gl4pipe->m_depthCompare = m_depthCompare;
  gl4pipe->m_cull = m_cull;
  gl4pipe->m_cullface = m_cullface;
  gl4pipe->m_frontface = m_frontface;
  gl4pipe->m_viewport = m_viewport;
  gl4pipe->m_scissor = m_scissor;
  gl4pipe->m_shaderProgram = m_shaderProgram;
  gl4pipe->m_topology = m_topology;
  gl4pipe->m_polygon = m_polygon;
  gl4pipe->m_viewport = m_viewport;
  gl4pipe->m_scissor = m_scissor;
  for (auto &shader : shaders) {  
    gl4pipe->shaders[shader.second->GetShaderStage()] = shader.second;
    inherited.m_shaders.push_back(shader.second);
  }
}


Shader *GL4GraphicsPipelineState::GetShader(ShaderStage stage)
{
  auto it = shaders.find(stage);
  if (it == shaders.end()) {  
    return nullptr;
  }
  return it->second;
}


DepthCompare GL4GraphicsPipelineState::GetDepthCompare() const
{
  switch (m_depthCompare) {
    case GL_LESS: return DepthCompare::vikr_DEPTH_LESS;
    case GL_GREATER: return DepthCompare::vikr_DEPTH_GREATER;
    case GL_GEQUAL: return DepthCompare::vikr_DEPTH_GEQUAL;
    case GL_LEQUAL: return DepthCompare::vikr_DEPTH_LEQUAL;
    case GL_EQUAL: return DepthCompare::vikr_DEPTH_EQUAL;
    case GL_ALWAYS: return DepthCompare::vikr_DEPTH_ALWAYS;
    case GL_NEVER: return DepthCompare::vikr_DEPTH_NEVER;
    case GL_NOTEQUAL: return DepthCompare::vikr_DEPTH_NOTEQUAL;
    default: return DepthCompare::vikr_DEPTH_LESS;
  }
}


BlendEq GL4GraphicsPipelineState::GetBlendEquation() const
{
  switch (m_blendeq) {
    case GL_FUNC_ADD: return BlendEq::vikr_BLEND_ADD;
    case GL_FUNC_REVERSE_SUBTRACT: return BlendEq::vikr_BLEND_REVERSE_SUBTRACT;
    case GL_FUNC_SUBTRACT: return BlendEq::vikr_BLEND_SUBTRACT;
    default: return BlendEq::vikr_BLEND_ADD;
  }
}


BlendFactor GetBlendFactorFromNative(GLenum native)
{
  switch (native) {
  case GL_CONSTANT_ALPHA: return BlendFactor::vikr_BLEND_CONSTANT_ALPHA;
  case GL_CONSTANT_COLOR: return BlendFactor::vikr_BLEND_CONSTANT_COLOR;
  case GL_DST_ALPHA: return BlendFactor::vikr_BLEND_DST_ALPHA;
  case GL_DST_COLOR: return BlendFactor::vikr_BLEND_DST_COLOR;
  case GL_ONE_MINUS_CONSTANT_ALPHA: return BlendFactor::vikr_BLEND_ONE_MINUS_CONSTANT_ALPHA;
  case GL_ONE: return BlendFactor::vikr_BLEND_ONE;
  case GL_ONE_MINUS_CONSTANT_COLOR: return BlendFactor::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR;
  case GL_ONE_MINUS_DST_ALPHA: return BlendFactor::vikr_BLEND_ONE_MINUS_DST_ALPHA;
  case GL_ONE_MINUS_DST_COLOR: return BlendFactor::vikr_BLEND_ONE_MINUS_DST_COLOR;
  case GL_ONE_MINUS_SRC_ALPHA: return BlendFactor::vikr_BLEND_ONE_MINUS_SRC_ALPHA;
  case GL_ONE_MINUS_SRC_COLOR: return BlendFactor::vikr_BLEND_ONE_MINUS_SRC_COLOR;
  case GL_SRC_ALPHA: return BlendFactor::vikr_BLEND_SRC_ALPHA; 
  case GL_SRC_COLOR: return BlendFactor::vikr_BLEND_SRC_COLOR;
  case GL_ZERO: return BlendFactor::vikr_BLEND_ZERO;
  default: return BlendFactor::vikr_BLEND_ONE_MINUS_SRC_ALPHA;
  }
}


BlendFactor GL4GraphicsPipelineState::GetBlendFactorSrc() const
{
  return GetBlendFactorFromNative(m_blendsrc);
}


BlendFactor GL4GraphicsPipelineState::GetBlendFactorDst() const
{
  return GetBlendFactorFromNative(m_blenddst);
}


Topology GL4GraphicsPipelineState::GetTopology() const
{
  switch (m_topology) {
    case GL_LINES: return Topology::VIKR_LINES;
    case GL_TRIANGLES: return Topology::VIKR_TRIANGLES;
    case GL_POINTS: return Topology::VIKR_POINTS;
    case GL_TRIANGLE_FAN: return Topology::VIKR_TRIANGLE_FAN;
    case GL_LINE_STRIP: return Topology::VIKR_TRIANGLE_STRIP;
    case GL_TRIANGLE_STRIP_ADJACENCY: return Topology::VIKR_TRIANGLE_STRIP_ADJACENCY;
    default: return Topology::VIKR_TRIANGLES;
  }
}
} // vikr