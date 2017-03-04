//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/renderer/skybox.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/math/geometry/cube.hpp>
#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/renderer/renderer.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/scene/camera.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace vikr {


Skybox::Skybox()
{
}


vvoid Skybox::Init(RenderDevice *device, ResourceManager *mgr) {
  m_device = device;
  m_mgr = mgr;

  cubemap = device->CreateCubemap();
  skybox_input = {
    "../../../libs/models/skybox/right.jpg",
    "../../../libs/models/skybox/left.jpg",
    "../../../libs/models/skybox/top.jpg",
    "../../../libs/models/skybox/bottom.jpg",
    "../../../libs/models/skybox/back.jpg",
    "../../../libs/models/skybox/front.jpg",
  };
  cubemap->Load(&skybox_input);

  Shader *vert_skybox = device->CreateShader("vert_skybox", vikr_VERTEX_SHADER);
  Shader *frag_skybox = device->CreateShader("frag_skybox", vikr_FRAGMENT_SHADER);
  vert_skybox->Compile("../../../libs/shader/GLSL/skybox.vert");
  frag_skybox->Compile("../../../libs/shader/GLSL/skybox.frag");
  program = device->CreateShaderProgram();
  program->LoadShader(vert_skybox);
  program->LoadShader(frag_skybox);
  program->Build();

  

  Cube cube;
  skybox = mgr->CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), cube.GetIndices());
  skybox->Build(device);
  sky_cmd.m_mesh = skybox;

  list = device->CreateCommandbufferList();
}


vvoid Skybox::Execute() {
  // Grab camera perspective and view.
  // Don't forget the pipelinestate!
  ICamera *cam = Renderer::GetRenderer()->GetCamera();
  GraphicsPipelineState *pipeline = m_device->GetContext()->GetGraphicsPipelineState();
  Commandbuffer &buf = m_device->CreateCommandbuffer(list);
  sky_cmd.Record(buf);
  pipeline->SetShaderProgram(program);
  pipeline->SetDepthFunc(DepthFunc::vikr_DEPTH_LEQUAL);
  pipeline->SetCullMode(false);
  pipeline->Update();
  Material mat;
  mat.SetMat4("vikr_View", glm::mat4(glm::mat3(cam->GetView())));
  mat.SetMat4("vikr_Projection", cam->GetProjection());
  mat.SetCubemap("skybox", cubemap, 0);
  ShaderUniformParams params;
  params.samplers = mat.GetUniformSamplers();
  params.uniforms = mat.GetMaterialValues();
  m_device->GetContext()->SetShaderUniforms(&params);
  m_device->GetContext()->ExecuteCommands(list);
  pipeline->SetCullMode(true);
  pipeline->SetDepthFunc(DepthFunc::vikr_DEPTH_LESS);
  list->Clear();
}
} // vikr