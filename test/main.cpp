/*

  Going to be cleaned up soon...
*/
#include <iostream>
#include <shader/shader.hpp>
#include <vikr.hpp>
#include <math/shape/cube.hpp>
#include <math/shape/sphere.hpp>
#include <util/vikr_log.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <shader/material.hpp>
#include <scene/camera.hpp>
#include <shader/texture.hpp>
#include <math/shape/quad.hpp>
#include <lighting/point_light.hpp>
#include <scene/first_person_camera.hpp>
#include <resources/resource_manager.hpp>
#include <scene/scene_node.hpp>
#include <renderer/command/debug_command.hpp>
#include <renderer/command/mesh_command.hpp>
#include <scene/components/transform_component.hpp>
#include <scene/components/renderer_component.hpp>
#include <scene/components/mesh_component.hpp>
#include <glm/gtx/compatibility.hpp>

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
  camera.SetClip(0.1, 1000);
  camera.SetFOV(45.0f);
  camera.SetSpeed(5.0f);
  camera.SetSensitivity(0.50f);
  camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
  LoadGlad();
  // Options 
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // Initialize the renderer.
  InitVikrEngine(vikr_OPENGL);
  SceneNode *node = ResourceManager::GetResourceManager()->CreateSceneNode();
  Renderer::GetRenderer()->SetCamera(&camera);
  Texture *texture = ResourceManager::GetResourceManager()->CreateTexture(vikr_TEXTURE_2D, "awesomeface.png", true);
  Mesh *mesh;
  Mesh *cube2;
  Mesh *line_mesh;
  Mesh *meshlight;
  MeshCommand mesh_command1;
  MeshCommand mesh_command3;
  MeshCommand mesh_command2;
  DebugCommand p_command;
  Cube cube;
  PointLight light;
  std::vector<glm::vec3> line = {
    glm::vec3(4.0f, 4.0f, 4.0f),
    glm::vec3(5.0f, 5.0f, 5.0f)
  };
  light.SetDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
  // Storing shaders into resources from renderer.
  ResourceManager::GetResourceManager()->StoreShader("test", "test.vert", "test.frag", "../../libs/shader/GLSL");
  ResourceManager::GetResourceManager()->StoreShader("light", "test.vert", "light.frag");
  mesh = ResourceManager::GetResourceManager()->CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs());
  cube2 = ResourceManager::GetResourceManager()->CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs());
  meshlight = ResourceManager::GetResourceManager()->CreateMesh(cube.GetVertices(), cube.GetNormals(), cube.GetUVs());
  line_mesh = ResourceManager::GetResourceManager()->CreateMesh(line, std::vector<glm::vec3>(), std::vector<glm::vec2>());
  mesh->Create();
  cube2->Create();
  meshlight->Create(); 
  line_mesh->Create();
  /**
    referencing stored shaders with materials. 
  */
  Material material(ResourceManager::GetResourceManager()->GetShader("test"));
  Material lightMaterial(ResourceManager::GetResourceManager()->GetShader("light"));
  /**
    Create meshes.
  */
  
  /**
    Reference the materials and meshes into mesh command. 
  */
  mesh_command1.SetMaterial(&material);
  mesh_command3.SetMaterial(&material);
  mesh_command2.SetMaterial(&lightMaterial);
  mesh_command1.SetMesh(mesh);
  mesh_command2.SetMesh(meshlight);
  mesh_command3.SetMesh(cube2);
  p_command.SetMesh(line_mesh);
  p_command.SetLineWidth(20);
  light.SetPos(glm::vec3(0.0f, 0.0f, 0.0f));

  // SceneNode Configs.
  TransformComponent *t = 
    static_cast<TransformComponent *>
    (ResourceManager::GetResourceManager()->CreateComponent(vikr_COMPONENT_TRANSFORM));
  t->transform.Position = glm::vec3(1.0f, 0.0f, -1.0f);
  MeshComponent *mc = 
    static_cast<MeshComponent *>
    (ResourceManager::GetResourceManager()->CreateComponent(vikr_COMPONENT_MESH));
  mc->mesh = mesh;
  RendererComponent *rc = 
    static_cast<RendererComponent *>
    (ResourceManager::GetResourceManager()->CreateComponent(vikr_COMPONENT_RENDERER));
    rc->material = &material;
  node->AddComponent(t);
  node->AddComponent(mc);
  node->AddComponent(rc);
  node->Update();

  /**
    Set the variables of the shaders associated with the material. 
  */
  material.SetVector3fv("obj_diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
  material.SetVector3fv("obj_specular", glm::vec3(1.0f, 1.0f, 1.0f));
  material.SetTexture("texas", texture, 0);
  lightMaterial.SetVector3fv("light_color", light.GetColor());

  // Standard Game Loop
  vreal32 radius = 2.0f;
  vreal32 angle = 0.0f;
  while(!WindowShouldClose(window)) {
    CalculateDeltaTime();
    PollEvents();
    Do_Movement();
    VikrLog::DisplayMessage(VIKR_NORMAL, std::to_string(GetFPS()));
    camera.Update();
    glm::mat4 model;
    angle += GetDeltaTime() * 100;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    mesh_command1.SetTransform(model);
    light.SetPos(glm::vec3(std::sin(GetTime()) * radius, std::cos(GetTime()) * radius, 0.0f));
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
    mesh_command3.SetTransform(model);
    model = glm::mat4();
    model = glm::translate(model, light.GetPos());
    model = glm::scale(model, glm::vec3(0.2f));
    mesh_command2.SetTransform(model);
    t->transform.Position = glm::lerp(t->transform.Position, glm::vec3(0.0f, 5.0f, 0.0f), GetDeltaTime());
    glm::quat r = glm::angleAxis(glm::radians(90.0f), t->transform.Up);
    r *= glm::angleAxis(glm::radians(90.f), t->transform.Front);
    t->transform.Rotation = glm::slerp(t->transform.Rotation, r, GetDeltaTime());
    t->Update();
    /**
      Push back the mesh_commands and light!
    */
    Renderer::GetRenderer()->PushBack(&mesh_command1);
    Renderer::GetRenderer()->PushBack(&mesh_command2);
    Renderer::GetRenderer()->PushBack(&mesh_command3);
    Renderer::GetRenderer()->PushBack(node);
    Renderer::GetRenderer()->PushBack(&p_command);
    Renderer::GetRenderer()->PushBack(&light);
    Renderer::GetRenderer()->Render();
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