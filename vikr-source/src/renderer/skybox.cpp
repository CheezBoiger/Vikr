//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/renderer/skybox.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/math/shape/cube.hpp>
#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/renderer/renderer.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/scene/camera.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace vikr {


Skybox::Skybox()
{
}


vvoid Skybox::Init(RenderDevice *device) {
  m_device = device;

  cubemap = device->CreateCubemap();
  skybox_input = {
    "../../libs/models/skybox/right.jpg",
    "../../libs/models/skybox/left.jpg",
    "../../libs/models/skybox/top.jpg",
    "../../libs/models/skybox/bottom.jpg",
    "../../libs/models/skybox/back.jpg",
    "../../libs/models/skybox/front.jpg",
  };
  cubemap->Load(&skybox_input);

  ResourceManager *mgr = device->GetResourceManager();
  Shader *vert_skybox = mgr->CreateShader("vert_skybox", VERTEX_SHADER);
  Shader *frag_skybox = mgr->CreateShader("frag_skybox", FRAGMENT_SHADER);
  vert_skybox->Compile("../../libs/shader/GLSL/skybox.vert");
  frag_skybox->Compile("../../libs/shader/GLSL/skybox.frag");
  program = device->GetResourceManager()->CreateShaderProgram();
  program->LoadShader(vert_skybox);
  program->LoadShader(frag_skybox);
  program->Build();

  

  Cube cube;
  skybox = mgr->CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), cube.GetIndices());
  skybox->Build(device);
  sky_cmd.m_mesh = skybox;

  mgr->DestroyShader("vert_skybox");
  mgr->DestroyShader("frag_skybox");
}


vvoid Skybox::Execute() {
  // Grab camera perspective and view.
  // Don't forget the pipelinestate!
  ICamera *cam = Renderer::GetRenderer()->GetCamera();
  PipelineState *pipeline = m_device->GetContext()->GetPipelineState();
  std::unique_ptr<Commandbuffer> buf = m_device->CreateCommandbuffer();
  sky_cmd.Record(buf.get());
  list.PushBack(buf);
  pipeline->SetShaderProgram(program);
  pipeline->SetDepthFunc(DepthFunc::vikr_DEPTH_LEQUAL);
  pipeline->SetCullMode(false);
  pipeline->Update();
  Material mat;
  mat.SetMat4("vikr_View", glm::mat4(glm::mat3(cam->GetView())));
  mat.SetMat4("vikr_Projection", cam->GetProjection());
  mat.SetCubemap("skybox", cubemap.get(), 0);
  ShaderUniformParams params;
  params.samplers = mat.GetUniformSamplers();
  params.uniforms = mat.GetMaterialValues();
  m_device->GetContext()->SetShaderUniforms(&params);
  m_device->GetContext()->ExecuteCommands(&list);
  pipeline->SetCullMode(true);
  pipeline->SetDepthFunc(DepthFunc::vikr_DEPTH_LESS);
  list.Clear();
}
} // vikr