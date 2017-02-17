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
  std::vector<const vchar *> input = {
    "../../libs/models/skybox/right.jpg",
    "../../libs/models/skybox/left.jpg",
    "../../libs/models/skybox/top.jpg",
    "../../libs/models/skybox/bottom.jpg",
    "../../libs/models/skybox/back.jpg",
    "../../libs/models/skybox/front.jpg",
  };
  cubemap->Load(input);

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

  ICamera *cam = Renderer::GetRenderer()->GetCamera();
  cam_cmd.camera = cam;
  std::unique_ptr<Commandbuffer> buf_cam = m_device->CreateCommandbuffer();
  cam_cmd.Record(buf_cam.get());
  list.PushBack(buf_cam);

  std::unique_ptr<Commandbuffer> buf = device->CreateCommandbuffer();
  sky_cmd.Record(buf.get());
  list.PushBack(buf);

}

#include <vikr/graphics/gl4/gl4_vertexbuffer.hpp>


vvoid Skybox::Draw() {
  m_device->GetContext()->GetPipelineState()->SetShaderProgram(program);
  m_device->GetContext()->GetPipelineState()->Update();
  Material mat;
  mat.SetInt("skybox", 0);
  ShaderUniformParams params;
  /**
    TODO(): Problem with cubemap not seen. Could this be because of the shaders?
            Mesh isn't being seen either?
  */
  params.samplers = mat.GetUniformSamplers();
  params.uniforms = mat.GetMaterialValues();
  m_device->GetContext()->SetShaderUniforms(&params);
  glDisable(GL_CULL_FACE);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->GetNativeId());
  m_device->GetContext()->ExecuteCommands(&list);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  glEnable(GL_CULL_FACE);
  VIKR_ASSERT(glGetError() == 0);
}
} // vikr