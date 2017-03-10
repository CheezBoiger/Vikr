/*
  OpenGL Sample test.
*/
#include <iostream>
#include <vikr/vikr.hpp>
#include <vikr/math/geometry/cube.hpp>
#include <vikr/scene/camera.hpp>
#include <vikr/lighting/point_light.hpp>
#include <vikr/lighting/directional_light.hpp>
#include <vikr/scene/first_person_camera.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/resources/model_loader.hpp>
#include <vikr/scene/scene_node.hpp>
#include <vikr/renderer/deferred_renderer.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/scene/components/transform_component.hpp>
#include <vikr/scene/components/renderer_component.hpp>
#include <vikr/scene/components/mesh_component.hpp>
#include <vikr/scene/components/light_component.hpp>
#include <vikr/input/window.hpp>
#include <vikr/input/mouse.hpp>
#include <vikr/input/keyboard.hpp>
#include <vikr/graphics/gl4/gl4_device.hpp>
#include <vikr/math/geometry/sphere.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/shader/shader_program.hpp>


using namespace vikr;
unsigned int screen_width = 1200;
unsigned int screen_height = 800;
FPSCamera camera(89.0f, glm::vec3(0.0f, 5.0f, 5.0f));


void Do_Movement()
{
  // Camera controls
  if(Keyboard::IsPressed(Keyboard::KEY_W) || Keyboard::IsRepeating(Keyboard::KEY_W))
    camera.Move(FORWARD, static_cast<vreal32>(GetDeltaTime()));
  if(Keyboard::IsPressed(Keyboard::KEY_S) || Keyboard::IsRepeating(Keyboard::KEY_S))
    camera.Move(BACK, static_cast<vreal32>(GetDeltaTime()));
  if(Keyboard::IsPressed(Keyboard::KEY_A) || Keyboard::IsRepeating(Keyboard::KEY_A))
    camera.Move(LEFT, static_cast<vreal32>(GetDeltaTime()));
  if(Keyboard::IsPressed(Keyboard::KEY_D) || Keyboard::IsRepeating(Keyboard::KEY_D))
    camera.Move(RIGHT, static_cast<vreal32>(GetDeltaTime()));
}


int main(int c, char* args[]) {
  InitVikr(vikr_PIPELINE_OPENGL);
  Window win = Window::CreateVikrWindow(screen_width, screen_height, "Vikr OpenGL");
  Window::SetMainWindow(&win);
  // Options.
  Keyboard::RegisterKeyboardCallback(Keyboard::DefaultKeyCallback);
  Mouse::RegisterMouseCallback(Mouse::DefaultMouseCallback);
  Mouse::SetMouseMode(Mouse::Mode::MOUSE_CURSOR_DISABLED);

  camera.SetViewport(0, 0, screen_width, screen_height);
  camera.SetClip(0.1, 10000);
  camera.SetFOV(45.0f);
  camera.SetSpeed(30.0f);
  camera.SetSensitivity(0.50f);
  camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

  GL4RenderDevice device;
  DeferredRenderer renderer;
  ResourceManager mgr;
  renderer.SetCamera(&camera);
  renderer.Init(&device, &mgr);
#define SPONZA 1
#if SPONZA
  SceneNode *node = ModelLoader::ImportModel(renderer.GetDevice(), &mgr,
    "../../../libs/models/sponza_cry/sponza.obj", "sponza", false);
  SceneNode *nano = ModelLoader::ImportModel(renderer.GetDevice(), &mgr,
    "../../../libs/models/nanosuit/nanosuit.obj", "suitboy", true);

  // suitboy.
  TransformComponent *suitcomp = nano->AddComponent<TransformComponent>();
  suitcomp->transform.Scale = glm::vec3(0.5f);
  nano->Update();
  
  // sponza
  TransformComponent *comp = node->AddComponent<TransformComponent>();
  comp->transform.Scale = glm::vec3(0.05f);
  comp->transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
  node->Update();
#endif
  // Light components
  Cube cube;
  Sphere sphere(1.0f, 6);
  Mesh *cube_mesh = 
    mgr.CreateMesh();
  cube_mesh->Build(&device, vikr_STATIC, cube.GetVertices(), cube.GetIndices());
  Mesh *light_mesh =
    //mgr.CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), cube.GetIndices());
    mgr.CreateMesh();
  light_mesh->Build(renderer.GetDevice(), vikr_STATIC, sphere.GetVertices(), sphere.GetIndices());

  SceneNode *cube1 = mgr.CreateSceneNode();
  cube1->AddComponent<MeshComponent>()->mesh = cube_mesh;
  cube1->AddComponent<TransformComponent>();
  //cube1->AddComponent<RendererComponent>()->material = default_mat;
  cube1->Update();


  // Directional light program...
  ShaderProgram *directional_depthProgram = device.CreateShaderProgram();
  Shader *directional_vert = device.CreateShader("directional_vert", vikr_VERTEX_SHADER);
  Shader *directional_frag = device.CreateShader("directional_frag", vikr_FRAGMENT_SHADER);
  directional_vert->Compile("../../../libs/shader/GLSL/directional_shadowdepth.vert");
  directional_frag->Compile("../../../libs/shader/GLSL/directional_shadowdepth.frag");
  directional_depthProgram->LoadShader(directional_vert);
  directional_depthProgram->LoadShader(directional_frag);
  directional_depthProgram->Build();

  PointLight plight;
  PointLight plight2;

  DirectionalLight dlight1;
  Material light_mtl;
  Texture *light_albedo = device.CreateTexture("light_albedo", vikr_TARGET_2D, 
    "../../../samples/sphere.png", true);
  Texture *light_normal = device.CreateTexture("light_normal", vikr_TARGET_2D,
    "../../../samples/sphere_norm.png", true);
  Texture *light_spec = device.CreateTexture("light_amb", vikr_TARGET_2D,
    "../../../samples/sphere_spec.png", true);
  light_albedo->Finalize(); 
  light_normal->Finalize();
  light_spec->Finalize();
  light_mtl.SetTexture("vikr_TexAlbedo", light_albedo, 0);
  light_mtl.SetTexture("vikr_TexNormal", light_normal, 1);
  light_mtl.SetTexture("vikr_TexSpecular", light_spec, 2);
  SceneNode *light_object = mgr.CreateSceneNode();
  TransformComponent *light_c = light_object->AddComponent<TransformComponent>();
  light_c->transform.Position = glm::vec3(5.0f, 5.0f, 5.0f);
  RendererComponent *lrc = light_object->AddComponent<RendererComponent>();
  lrc->material = &light_mtl;
  MeshComponent *mc = light_object->AddComponent<MeshComponent>();
  mc->mesh = light_mesh;
  SceneNode *light_node = mgr.CreateSceneNode();
  LightComponent *lc = light_node->AddComponent<LightComponent>();
  lc->light = &plight;
  plight.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));

  SceneNode *light_node2 = mgr.CreateSceneNode();
  LightComponent *lc2 = light_node2->AddComponent<LightComponent>();
  lc2->light = &plight2;
  plight2.SetPos(glm::vec3(0.0f, 10.0f, 0.0f));
  plight2.SetDiffuse(glm::vec3(1.0f, 0.0f, 0.0f));
  plight2.SetSpecular(glm::vec3(1.0f, 0.0f, 0.0f));
  light_node2->Update();

  SceneNode *dlight_obj = mgr.CreateSceneNode();
  MeshComponent *dmesh = dlight_obj->AddComponent<MeshComponent>();
  dmesh->mesh = light_mesh;
  TransformComponent *dlight_t = dlight_obj->AddComponent<TransformComponent>();
  

  SceneNode *dlight_node1 = mgr.CreateSceneNode();
  LightComponent *dc1 = dlight_node1->AddComponent<LightComponent>();
  dc1->light = &dlight1;
  dlight1.Init(&device, directional_depthProgram);
  dlight1.SetPos(glm::vec3(-10.0f, 80.0f, -10.0f));
  dlight1.Update();
  dc1->Update();

  light_object->AddChild(light_node);
  light_object->Update();

  dlight_obj->AddChild(dlight_node1);
  dlight_obj->Update();

  while (!Window::GetMainWindow()->IsClosed()) {
    CalculateDeltaTime();
    PollEvents();
    Do_Movement();
    VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(GetFPS()) + " Frames/s");
    camera.Update(static_cast<vreal32>(GetDeltaTime()));

    lc->light->SetPos(glm::vec3(std::sin(GetTime()) * 50.0f, 5.0f, 5.0f));
    dlight1.SetPos(glm::vec3(-50.0f * std::sin(GetTime()), dlight1.GetPos().y, dlight1.GetPos().z));
    //lc->light->SetDiffuse(glm::vec3(0.0f, -std::sin(GetTime()), std::sin(GetTime()))); 
    //lc->light->SetSpecular(lc->light->GetDiffuse());
    light_c->transform.Position = lc->light->GetPos();
    light_c->Update(); 

    dlight_t->transform.Position = dlight1.GetPos();
    dlight_obj->Update();
    renderer.PushBack(light_object);
    renderer.PushBack(light_node2);
    renderer.PushBack(dlight_obj);
#if SPONZA
    renderer.PushBack(node);
    renderer.PushBack(nano);
#endif
    renderer.Render();

    renderer.Present();
  }
/*
  // Vulkan workbench
  InitVikr(vikr_PIPELINE_VULKAN);
  Window win = Window::CreateVikrWindow(screen_width, screen_height, "Vikr");
  Window::SetMainWindow(&win);
  // Options.
  Keyboard::RegisterKeyboardCallback(Keyboard::DefaultKeyCallback);
  Mouse::RegisterMouseCallback(Mouse::DefaultMouseCallback);
  Mouse::SetMouseMode(Mouse::Mode::MOUSE_CURSOR_DISABLED);

  camera.SetViewport(0, 0, screen_width, screen_height);
  camera.SetClip(0.1, 10000);
  camera.SetFOV(45.0f);
  camera.SetSpeed(30.0f);
  camera.SetSensitivity(0.50f);
  camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));


  VKDevice device;
  // Another standard game loop
  while (!Window::GetMainWindow()->IsClosed()) {
    CalculateDeltaTime();
    PollEvents();
  }
*/
  vikr::Cleanup();
  return 0;
}