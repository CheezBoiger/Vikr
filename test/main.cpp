#include <iostream>
#include <shader/gl_shader.hpp>


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

  // Options 
  //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }

  //std::cout << "c(^ vv ^  c)" << std::endl;
  //vikr::GLShader vs(vikr::vikr_VERTEX_SHADER, "");
  //vikr::GLShader fs(vikr::vikr_FRAGMENT_SHADER, "");
  //vikr::Shader shader;
  //shader.Link(&vs, &fs);

  // Standard Game Loop
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glfwSwapBuffers(window);
  }
  return 0;
}