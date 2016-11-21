#include <iostream>
#include <shader/gl_shader.hpp>
#include <shader/shader.hpp>
#include <vikr.hpp>
#include <mesh/mesh.hpp>
#include <math/shape/cube.hpp>
#include <util/vikr_log.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <shader/material.hpp>
#include <scene/camera.hpp>
#include <util/vikr_assert.hpp>
#include <shader/texture.hpp>
#include <math/shape/quad.hpp>
#include <scene/first_person_camera.hpp>

using namespace vikr;
unsigned int screen_width = 1200;
unsigned int screen_height = 800;
vbool firstMouse = true;
FPSCamera camera(89.0f, glm::vec3(0.0f, 1.0f, 5.0f));
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

  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;
  camera.Look(xoffset, yoffset, GetDeltaTime());
}


int main(int c, char* args[]) {
  glfwInit();
  VikrWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.3);
  VikrWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  VikrWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  VikrWindowHint(GLFW_RESIZABLE, GL_FALSE);


  GLFWwindow* window = VikrCreateGLFWwindow(screen_width, screen_height, "Vikr", nullptr, nullptr); // Windowed
  VikrMakeContextCurrent(window);
  camera.SetViewport(0, 0, screen_width, screen_height);
  camera.SetClip(0.1, 1000);
  camera.SetFOV(45.0f);
  camera.SetSpeed(10.0f);
  camera.SetSensitivity(0.50f);
  camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
  LoadGlad();
  // Options 
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  VikrLog::UnSupress(VIKR_RUNTIME_DEBUG);
  VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "c(^ vv ^  c)");
  GLShader vs(vikr_VERTEX_SHADER, "test.vert");
  GLShader fs(vikr_FRAGMENT_SHADER, "test.frag");
  Shader shader;
  shader.Link(&vs, &fs);
  Texture texture = Texture::Generate("awesomeface.png", false);
  Cube cube;
  Quad quad;
  Mesh mesh;
  Mesh mesh2;
  mesh.Create(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), std::vector<vuint32>());
  mesh2.Create(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), std::vector<vuint32>());
  mesh.SetName("Red Cube");
  Material material(&shader);
  mesh.SetMaterial(&material);
  mesh.SetTexture(&texture);
  mesh2.SetMaterial(&material);
  mesh2.SetTexture(&texture);
  Renderer *renderer = InitVikrEngine(vikr_OPENGL);
  renderer->SetClearColor(glm::vec3(0.4f, 0.4f, 0.4f));
  renderer->SetCamera(&camera);
  Renderer::SetRenderer(renderer);
  glEnable(GL_DEPTH_TEST); // This shouldn't be hardcoded...
  // Standard Game Loop
  while(!WindowShouldClose(window)) {
    CalculateDeltaTime();
    //camera.Move(CamDirection::LEFT, GetDeltaTime());
    std::string str = "x: " + std::to_string(camera.GetPos().x) + " y: " + std::to_string(camera.GetPos().y) + " z: " + std::to_string(camera.GetPos().z);
    VikrLog::DisplayMessage(VIKR_NORMAL, str);
    camera.Update();
    PollEvents();
    Do_Movement();
    // Just testing the clear color function...
    vreal64 oscillate = std::abs(std::sin(vikr::GetTime()));
    vreal64 roscillate = 1.0f - oscillate;
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(std::sin(GetTime()), 0.0f, 0.0f));
    mesh.GetMeshCommand()->SetTransform(model);
    model = glm::mat4();
    model = glm::translate(model, glm::vec3(1.0f, 1.0f, 1.0f));
    mesh2.GetMeshCommand()->SetTransform(model);
    Renderer::GetRenderer()->PushBack(mesh.GetMeshCommand()); 
    Renderer::GetRenderer()->PushBack(mesh2.GetMeshCommand());
    //Renderer::GetRenderer()->SetClearColor(glm::vec3(oscillate, 0.0f, roscillate)); 
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