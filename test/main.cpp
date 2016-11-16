#include <iostream>
#include <shader/gl_shader.hpp>
#include <shader/shader.hpp>
#include <vikr.hpp>
#include <util/vikr_log.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


unsigned int screen_width = 1200;
unsigned int screen_height = 800;


int main(int c, char* args[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


  GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Vikr", nullptr, nullptr); // Windowed
  glfwMakeContextCurrent(window);

  vikr::LoadGlad();
  // Options 
  //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  vikr::VikrLog::DisplayMessage(vikr::VIKR_NOTIFY, "c(^ vv ^  c)");
  vikr::GLShader vs(vikr::vikr_VERTEX_SHADER, "vert.vs");
  vikr::GLShader fs(vikr::vikr_FRAGMENT_SHADER, "metallic.fs");
  vikr::Shader shader;
  shader.Link(&vs, &fs);

  // Standard Game Loop
  while(!vikr::WindowShouldClose(window)) {
    vikr::CalculateDeltaTime();
    vikr::PollEvents();
    vikr::DoubleBufferSwap(window);
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
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}