#include <renderer/renderer.hpp>
//#include <renderer/render_command.hpp>
#include <shader/gl_shader.hpp>
#include <shader/vk_shader.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


Renderer *Renderer::renderer = nullptr;
std::unordered_map<std::string, std::pair<std::string, Shader*> > Renderer::shader_storage;


vvoid Renderer::LoadShader(Renderer *renderer, std::string shader_name, std::string fs, std::string vs) {
  Shader *shader = nullptr;
  switch (renderer->GetRenderType()) {
    case vikr_OPENGL: {
      GLShader vertex_shader(vikr_VERTEX_SHADER, vs);
      GLShader fragment_shader(vikr_FRAGMENT_SHADER, fs);
      shader = new Shader();
      shader->Link(&vertex_shader, &fragment_shader);
    }
    break;
    case vikr_VULKAN: {
      VikrLog::DisplayMessage(VIKR_NOTIFY, "SPIR-V NOT YET IMPLEMENTED! We are workin' on it ( = w = )");
    }
    default:
      VikrLog::DisplayMessage(VIKR_ERROR, "Renderer type is not known to this software!");
    break; 
  }
  if (shader->IsLinked()) {
    Renderer::shader_storage[shader_name] = std::make_pair(shader_name, shader);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, "Shader not linked! Aborting shader load!");
    delete shader; shader = nullptr; 
  }
}


Shader *Renderer::GetShader(std::string shader_name) {
  std::unordered_map<std::string, std::pair<std::string, Shader*>>::iterator it;
  Shader *shader = nullptr;
  it = shader_storage.find(shader_name);
  if (it != shader_storage.end()) {
    shader = shader_storage[shader_name].second;
  }
  return shader;
}


vvoid Renderer::PushBack(RenderCommand *command) {
  
  m_command_list.PushBack(command);
}
} // vikr