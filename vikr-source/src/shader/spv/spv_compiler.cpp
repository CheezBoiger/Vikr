//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <vikr/shader/spv/spv_compiler.hpp>

#include <vikr/util/vikr_log.hpp>
#include <vikr/shader/glsl/glsl_preprocessor.hpp>
#include <vikr/graphics/vk/vk_device.hpp>

#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>


namespace vikr {


const char *std_entry_point = "main";


const TBuiltInResource DefaultTBuiltInResource = {
    /* .MaxLights = */ 32,
    /* .MaxClipPlanes = */ 6,
    /* .MaxTextureUnits = */ 32,
    /* .MaxTextureCoords = */ 32,
    /* .MaxVertexAttribs = */ 64,
    /* .MaxVertexUniformComponents = */ 4096,
    /* .MaxVaryingFloats = */ 64,
    /* .MaxVertexTextureImageUnits = */ 32,
    /* .MaxCombinedTextureImageUnits = */ 80,
    /* .MaxTextureImageUnits = */ 32,
    /* .MaxFragmentUniformComponents = */ 4096,
    /* .MaxDrawBuffers = */ 32,
    /* .MaxVertexUniformVectors = */ 128,
    /* .MaxVaryingVectors = */ 8,
    /* .MaxFragmentUniformVectors = */ 16,
    /* .MaxVertexOutputVectors = */ 16,
    /* .MaxFragmentInputVectors = */ 15,
    /* .MinProgramTexelOffset = */ -8,
    /* .MaxProgramTexelOffset = */ 7,
    /* .MaxClipDistances = */ 8,
    /* .MaxComputeWorkGroupCountX = */ 65535,
    /* .MaxComputeWorkGroupCountY = */ 65535,
    /* .MaxComputeWorkGroupCountZ = */ 65535,
    /* .MaxComputeWorkGroupSizeX = */ 1024,
    /* .MaxComputeWorkGroupSizeY = */ 1024,
    /* .MaxComputeWorkGroupSizeZ = */ 64,
    /* .MaxComputeUniformComponents = */ 1024,
    /* .MaxComputeTextureImageUnits = */ 16,
    /* .MaxComputeImageUniforms = */ 8,
    /* .MaxComputeAtomicCounters = */ 8,
    /* .MaxComputeAtomicCounterBuffers = */ 1,
    /* .MaxVaryingComponents = */ 60,
    /* .MaxVertexOutputComponents = */ 64,
    /* .MaxGeometryInputComponents = */ 64,
    /* .MaxGeometryOutputComponents = */ 128,
    /* .MaxFragmentInputComponents = */ 128,
    /* .MaxImageUnits = */ 8,
    /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
    /* .MaxCombinedShaderOutputResources = */ 8,
    /* .MaxImageSamples = */ 0,
    /* .MaxVertexImageUniforms = */ 0,
    /* .MaxTessControlImageUniforms = */ 0,
    /* .MaxTessEvaluationImageUniforms = */ 0,
    /* .MaxGeometryImageUniforms = */ 0,
    /* .MaxFragmentImageUniforms = */ 8,
    /* .MaxCombinedImageUniforms = */ 8,
    /* .MaxGeometryTextureImageUnits = */ 16,
    /* .MaxGeometryOutputVertices = */ 256,
    /* .MaxGeometryTotalOutputComponents = */ 1024,
    /* .MaxGeometryUniformComponents = */ 1024,
    /* .MaxGeometryVaryingComponents = */ 64,
    /* .MaxTessControlInputComponents = */ 128,
    /* .MaxTessControlOutputComponents = */ 128,
    /* .MaxTessControlTextureImageUnits = */ 16,
    /* .MaxTessControlUniformComponents = */ 1024,
    /* .MaxTessControlTotalOutputComponents = */ 4096,
    /* .MaxTessEvaluationInputComponents = */ 128,
    /* .MaxTessEvaluationOutputComponents = */ 128,
    /* .MaxTessEvaluationTextureImageUnits = */ 16,
    /* .MaxTessEvaluationUniformComponents = */ 1024,
    /* .MaxTessPatchComponents = */ 120,
    /* .MaxPatchVertices = */ 32,
    /* .MaxTessGenLevel = */ 64,
    /* .MaxViewports = */ 16,
    /* .MaxVertexAtomicCounters = */ 0,
    /* .MaxTessControlAtomicCounters = */ 0,
    /* .MaxTessEvaluationAtomicCounters = */ 0,
    /* .MaxGeometryAtomicCounters = */ 0,
    /* .MaxFragmentAtomicCounters = */ 8,
    /* .MaxCombinedAtomicCounters = */ 8,
    /* .MaxAtomicCounterBindings = */ 1,
    /* .MaxVertexAtomicCounterBuffers = */ 0,
    /* .MaxTessControlAtomicCounterBuffers = */ 0,
    /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
    /* .MaxGeometryAtomicCounterBuffers = */ 0,
    /* .MaxFragmentAtomicCounterBuffers = */ 1,
    /* .MaxCombinedAtomicCounterBuffers = */ 1,
    /* .MaxAtomicCounterBufferSize = */ 16384,
    /* .MaxTransformFeedbackBuffers = */ 4,
    /* .MaxTransformFeedbackInterleavedComponents = */ 64,
    /* .MaxCullDistances = */ 8,
    /* .MaxCombinedClipAndCullDistances = */ 8,
    /* .MaxSamples = */ 4,
    /* .limits = */ {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
}};



SpvCompiler::SpvCompiler(VKRenderDevice *device, ShaderStage stage, std::string filepath)
  : filepath(filepath)
  , device(device)
  , shader_stage(stage)
  , compiled(false)
  , shaderModule(0)
{
}


vvoid SpvCompiler::Compile() {
  if (filepath.empty()) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Spir-V could not compile this shader module!"); 
    return;
  }
  LoadShaderFile();
}


vvoid SpvCompiler::GLSlangCompile(const vchar *source, vuint32 length)
{
  TBuiltInResource resources = DefaultTBuiltInResource;
  glslang::TProgram program;
  EShLanguage glslLanguage;
  switch (shader_stage) {
    case vikr_VERTEX_SHADER: glslLanguage = EShLangVertex; break;
    case vikr_FRAGMENT_SHADER: glslLanguage = EShLangFragment; break;
    case vikr_TESS_CONTROL_SHADER: glslLanguage = EShLangTessControl; break;
    case vikr_TESS_EVALUATION_SHADER: glslLanguage = EShLangTessEvaluation; break;
    case vikr_GEOMETRY_SHADER: glslLanguage = EShLangGeometry; break;
    case vikr_COMPUTE_SHADER: glslLanguage = EShLangCompute; break;
    default:  glslLanguage = EShLangVertex; break;
  }
  glslang::TShader shader(glslLanguage);

  shader.setStrings(&source, length);
  shader.setEntryPoint(std_entry_point);

  if (!shader.parse(&resources, 430, true, (EShMessages)(EShMsgVulkanRules | EShMsgSpvRules))) {
    compiled = false;
    VikrLog::DisplayMessage(VIKR_ERROR, "GLSlang failed to compile shader => " + filepath);
  }

  program.addShader(&shader);
  if (!program.link((EShMessages)(EShMsgVulkanRules | EShMsgSpvRules))) {
    compiled = false;
    VikrLog::DisplayMessage(VIKR_ERROR, "GLSlang failed to link shader => " + filepath);
  }

  compiled = true;
  std::vector<unsigned int> spirv;
  glslang::GlslangToSpv(*program.getIntermediate(glslLanguage), spirv);

  // Shader Modeule stuff.
  VkShaderModuleCreateInfo information;
  information.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  information.codeSize = spirv.size() * sizeof(vuint32);
  information.pCode = spirv.data();
  information.flags = 0;
  information.pNext = nullptr;
  if (vkCreateShaderModule(device->GetLogicalDevice(), &information, nullptr, &shaderModule) != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Failure to create SPV shader module => " + filepath);
    return;
  }
  // Determine the shader stage once again.
  switch (shader_stage) {
    case vikr_VERTEX_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
      break;
    case vikr_FRAGMENT_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
      break;
    case vikr_TESS_CONTROL_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
      break;
    case vikr_TESS_EVALUATION_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
      break;
    case vikr_GEOMETRY_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
      break;
    case vikr_COMPUTE_SHADER: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
      break;
    default: 
      pipelineShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
      break;
  }
  // Pipeline shader stage to be used by SpvShader.
  pipelineShaderStage.module = shaderModule;
  pipelineShaderStage.pName = std_entry_point;
}


vvoid SpvCompiler::LoadShaderFile() {
  std::string shader_code = preprocessor.Preprocess(filepath);
  GLSlangCompile(shader_code.c_str(), shader_code.length());
}


vvoid SpvCompiler::Cleanup()
{
  vkDestroyShaderModule(
    device->GetLogicalDevice(),
    shaderModule,
    nullptr
  );
}
} // vikr