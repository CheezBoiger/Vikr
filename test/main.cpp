#include <iostream>
#include <shader/gl_shader.hpp>
#include <vikr.hpp>
#include <util/vikr_log.hpp>


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

  //std::cout << "c(^ vv ^  c)" << std::endl;
  //vikr::GLShader vs(vikr::vikr_VERTEX_SHADER, "");
  //vikr::GLShader fs(vikr::vikr_FRAGMENT_SHADER, "");
  //vikr::Shader shader;
  //shader.Link(&vs, &fs);

  // Standard Game Loop
  while(!vikr::WindowShouldClose(window)) {
    vikr::internals::CalculateDeltaTime();
    vikr::PollEvents();
    vikr::DoubleBufferSwap(window);
  }
  return 0;
}