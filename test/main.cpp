#include <iostream>
#include <shader/gl_shader.hpp>
#include <shader/shader.hpp>
#include <vikr.hpp>
#include <mesh/mesh.hpp>
#include <math/shape/cube.hpp>
#include <util/vikr_log.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <shader/material.hpp>
#include <scene/camera.hpp>
#include <util/vikr_assert.hpp>
#include <shader/texture.hpp>
#include <math/shape/quad.hpp>

using namespace vikr;
unsigned int screen_width = 1200;
unsigned int screen_height = 800;
Camera cam(glm::vec3(0.0f, 5.0f, -5.0f));


int main(int c, char* args[]) {
  glfwInit();
  VikrWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.3);
  VikrWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  VikrWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  VikrWindowHint(GLFW_RESIZABLE, GL_FALSE);


  GLFWwindow* window = VikrCreateGLFWwindow(screen_width, screen_height, "Vikr", nullptr, nullptr); // Windowed
  VikrMakeContextCurrent(window);
  cam.SetViewport(0, 0, screen_width, screen_height);
  cam.SetClip(0.1, 1000);
  cam.SetFOV(45.0f);
  cam.SetSpeed(10.0f);
  LoadGlad();
  // Options 
  //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  VikrLog::UnSupress(VIKR_RUNTIME_DEBUG);
  VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "c(^ vv ^  c)");
  GLShader vs(vikr_VERTEX_SHADER, "test.vert");
  GLShader fs(vikr_FRAGMENT_SHADER, "test.frag");
  Shader shader;
  shader.Link(&vs, &fs);
  Texture texture = Texture::Generate("wall.jpg", false);
  Cube cube;
  Quad quad;
  Mesh mesh;
  mesh.Create(cube.GetVertices(), cube.GetNormals(), cube.GetUVs(), std::vector<vuint32>());
  mesh.SetName("Red Cube");
  Material material(&shader);
  mesh.SetMaterial(&material);
  mesh.SetTexture(&texture);
  Renderer *renderer = InitVikrEngine(vikr_OPENGL);
  renderer->SetClearColor(glm::vec3(0.4f, 0.4f, 0.4f));
  renderer->SetCamera(&cam);
  Renderer::SetRenderer(renderer);
  glEnable(GL_DEPTH_TEST); // This shouldn't be hardcoded...
  // Standard Game Loop
  while(!WindowShouldClose(window)) {
    CalculateDeltaTime();
    cam.Move(CamDirection::LEFT, GetDeltaTime());
    std::string str = "x: " + std::to_string(cam.GetPos().x) + " y: " + std::to_string(cam.GetPos().y) + " z: " + std::to_string(cam.GetPos().z);
    VikrLog::DisplayMessage(VIKR_NORMAL, str);
    cam.Update();
    PollEvents();
    // Just testing the clear color function...
    vreal64 oscillate = std::abs(std::sin(vikr::GetTime()));
    vreal64 roscillate = 1.0f - oscillate;
    Renderer::GetRenderer()->PushBack(mesh.GetMeshCommand());
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