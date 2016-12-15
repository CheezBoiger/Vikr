/*

  Going to be cleaned up soon...
*/
#include <iostream>
#include <shader/shader.hpp>
#include <vikr.hpp>
#include <math/shape/cube.hpp>
#include <util/vikr_log.hpp>
#include <glm/glm.hpp>
#include <shader/material.hpp>
#include <scene/camera.hpp>
#include <shader/texture.hpp>
#include <math/shape/quad.hpp>
#include <lighting/point_light.hpp>
#include <scene/first_person_camera.hpp>
#include <resources/resource_manager.hpp>
#include <resources/model_loader.hpp>
#include <scene/scene_node.hpp>
#include <renderer/command/debug_command.hpp>
#include <renderer/command/mesh_command.hpp>
#include <scene/components/transform_component.hpp>
#include <scene/components/renderer_component.hpp>
#include <scene/components/mesh_component.hpp>
#include <scene/components/camera_component.hpp>
#include <scene/components/light_component.hpp>
#include <graphics/gl4/gl4_device.hpp>
#include <math/shape/quad.hpp>
#include <glm/gtx/compatibility.hpp>
#include <graphics/gl4/gl4_device.hpp>

using namespace vikr;
unsigned int screen_width = 1200;
unsigned int screen_height = 800;
vbool firstMouse = true;
FPSCamera camera(89.0f, glm::vec3(0.0f, 5.0f, 5.0f));
vbool keys[1024];
double lastX = static_cast<double>(screen_width);
double lastY = static_cast<double>(screen_height);


void Do_Movement()
{
  // Camera controls
  if(keys[GLFW_KEY_W])
    camera.Move(FORWARD, GetDeltaTime());
  if(keys[GLFW_KEY_S])
    camera.Move(BACK, GetDeltaTime());
  if(keys[GLFW_KEY_A])
    camera.Move(LEFT, GetDeltaTime());
  if(keys[GLFW_KEY_D])
    camera.Move(RIGHT, GetDeltaTime());
}


// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if(key >= 0 && key < 1024)
  {
    if(action == GLFW_PRESS)
      keys[key] = true;
    else if(action == GLFW_RELEASE)
      keys[key] = false;
  }
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  vreal32 xoffset = static_cast<vreal32>(xpos - lastX);
  vreal32 yoffset = static_cast<vreal32>(lastY - ypos);

  lastX = xpos;
  lastY = ypos;
  camera.Look(xoffset, yoffset, GetDeltaTime());
}


int main(int c, char* args[]) {
  glfwInit();
  VikrWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  VikrWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  VikrWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  VikrWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = VikrCreateGLFWwindow(screen_width, screen_height, "Vikr", nullptr, nullptr); // Windowed
  VikrMakeContextCurrent(window);
  camera.SetViewport(0, 0, screen_width, screen_height);
  camera.SetClip(0.1, 10000);
  camera.SetFOV(45.0f);
  camera.SetSpeed(100.0f);
  camera.SetSensitivity(0.50f);
  camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
  LoadGlad();
  // Options 
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // Storing shaders into resources from renderer.
  VikrLog::UnSupress(VIKR_WARNING);
  GL4RenderDevice device;
  Renderer renderer;
  renderer.Init(&device);
  renderer.SetCamera(&camera);
  renderer.GetDevice()->StoreShader("test", "shaders/test.vert", "shaders/test.frag", "../../libs/shader/GLSL");
  renderer.GetDevice()->StoreShader("light", "shaders/test.vert", "shaders/light.frag");
  renderer.GetDevice()->StoreShader("screen", "shaders/screen_shader.vert", "shaders/screen_shader.frag");
  SceneNode *node = ModelLoader::ImportModel(renderer.GetDevice(), "common/sponza_obj/sponza.obj", "sponza");
  SceneNode *nano = ModelLoader::ImportModel(renderer.GetDevice(), "nanosuit/nanosuit.obj", "suitboy");
  Material *default_mat = renderer.GetDevice()->CreateMaterial("default_mat");
  default_mat->SetShader(renderer.GetDevice()->GetShader("test"));

  Material *light_mat = renderer.GetDevice()->CreateMaterial("light_mat");
  light_mat->SetShader(renderer.GetDevice()->GetShader("light"));
  light_mat->SetVector3fv("light_color", glm::vec3(1.0f, 1.0f, 1.0f));

  Quad quad;
  Cube cube;
  // suitboy.
  TransformComponent *suitcomp = nano->AddComponent<TransformComponent>();
  suitcomp->transform.Scale = glm::vec3(0.5f);
  nano->Update();
  
  // sponza
  TransformComponent *comp = node->AddComponent<TransformComponent>();
  comp->transform.Scale = glm::vec3(0.05f);
  comp->transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
  node->Update();
  Mesh *cube_mesh = 
    renderer.GetDevice()->
    GetResourceManager()->
    CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), cube.GetIndices());
  Mesh *light_mesh =
    renderer.GetDevice()->GetResourceManager()->
    CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), cube.GetIndices());
  cube_mesh->Create(renderer.GetDevice());
  light_mesh->Create(renderer.GetDevice());

  SceneNode *cube1 = renderer.GetDevice()->GetResourceManager()->CreateSceneNode();
  cube1->AddComponent<MeshComponent>()->mesh = cube_mesh;
  cube1->AddComponent<TransformComponent>();
  //cube1->AddComponent<RendererComponent>()->material = default_mat;
  cube1->Update();

  PointLight plight;
  PointLight plight2;
  SceneNode *light_object = renderer.GetDevice()->GetResourceManager()->CreateSceneNode();
  MeshComponent *mc = light_object->AddComponent<MeshComponent>();
  mc->mesh = light_mesh;
  TransformComponent *light_c = light_object->AddComponent<TransformComponent>();
  light_c->transform.Position = glm::vec3(5.0f, 5.0f, 5.0f);

  SceneNode *light_node = renderer.GetDevice()->GetResourceManager()->CreateSceneNode();
  LightComponent *lc = light_node->AddComponent<LightComponent>();
  lc->light = &plight;
  plight.SetDiffuse(glm::vec3(0.0f, 1.0f, 0.0f));

  SceneNode *light_node2 = renderer.GetDevice()->GetResourceManager()->CreateSceneNode();
  LightComponent *lc2 = light_node2->AddComponent<LightComponent>();
  lc2->light = &plight2;
  plight2.SetPos(glm::vec3(0.0f, 10.0f, 0.0f));
  plight2.SetDiffuse(glm::vec3(1.0f, 0.0f, 0.0f));
  plight2.SetSpecular(glm::vec3(1.0f, 0.0f, 0.0f));
  light_node2->Update();

  light_object->AddChild(light_node);
  light_object->Update();


  while(!WindowShouldClose(window)) {
    CalculateDeltaTime();
    PollEvents();
    Do_Movement();
    VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(GetFPS()) + " Frames/s");
    camera.Update();
    lc->light->SetPos(glm::vec3(std::sin(GetTime()) * 50.0f, 5.0f, 5.0f));
    light_c->transform.Position = lc->light->GetPos();
    light_c->Update();
    renderer.PushBack(light_object);
    renderer.PushBack(light_node2);
    renderer.PushBack(node);
    renderer.PushBack(nano);
    renderer.Render();
    DoubleBufferSwap(window);
  }

/*
  // Vulkan workbench
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
  uint32_t extension_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
  std::cout << extension_count << " extensions supported" << std::endl;
  glm::mat4 matrix;
  glm::vec4 vec;
  auto test = matrix * vec;

  // Another standard game loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
*/
  vikr::Cleanup();
  vikr::VikrDestroyWindow(window);
  vikr::VikrTerminateGLFW();
  return 0;
}