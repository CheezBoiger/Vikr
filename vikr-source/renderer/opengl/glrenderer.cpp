//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/opengl/glrenderer.hpp>
#include <renderer/renderer.hpp>

#include <shader/material.hpp>
#include <shader/glsl/glsl_shader.hpp>
#include <shader/stb/stb_image.h>
#include <shader/glsl/gl_texture.hpp>
#include <shader/glsl/gl_texture1d.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <shader/glsl/gl_texture3d.hpp>
#include <renderer/render_command.hpp>
#include <renderer/mesh_command.hpp>
#include <mesh/mesh.hpp>
#include <scene/camera.hpp>
#include <util/vikr_log.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <lighting/point_light.hpp>
#include <lighting/light.hpp>
#include <resources/opengl/gl_resources.hpp>

namespace vikr {


GLRenderer::GLRenderer()
  : Renderer(vikr_OPENGL)
{
}


vint32 GLRenderer::Init() {
  return true;
}

vint32 GLRenderer::StoreShader(std::string shader_name, 
                               std::string vs, 
                               std::string fs, 
                               std::string include_path) 
{
  GLSLShader shader;
  shader.SetIncludeSearchPath(include_path);
  shader.Compile(vs, fs);
  if (shader.IsLinked()) {
    return GLResources::StoreShader(shader_name, &shader);
  }
  return -1;
}


Shader *GLRenderer::GetShader(std::string shader_name) {
  return GLResources::GetShader(shader_name);
}


Texture *GLRenderer::CreateTexture(TextureTarget target, std::string img_path, vbool alpha) {
  Texture *texture = nullptr;
  vint32 width = 0;
  vint32 height = 0;
  vint32 depth = 0;
  vbyte *bytecode = stbi_load(img_path.c_str(), &width, &height, &depth,
                              alpha ? STBI_rgb_alpha : STBI_rgb);
  switch (target) {
    case vikr_TEXTURE_1D: texture = new GLTexture2D(width); break;
    case vikr_TEXTURE_2D: texture = new GLTexture2D(width, height); break;
    case vikr_TEXTURE_3D: texture = new GLTexture3D(width, height, depth); break;
    case vikr_TEXTURE_CUBEMAP: // not implemented yet.
    default: break;
  }
  if (texture) {
    texture->Create(bytecode);
    texture->SetString(img_path);
  }
  return texture;
}


vvoid GLRenderer::Render() {
  ClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);  
  ClearDisplay(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Sort out the m_command_list
  Sort();
  
  // Perform drawing, need to better understand passes for rendering,
  // Pre-batch, batch, and Post-batch drawing.
  std::vector<RenderCommand *> render_commands = m_command_list.GetCommandList();
  for (std::vector<RenderCommand *>::iterator it = render_commands.begin();
        it != render_commands.end();
        ++it) {
    switch ((*it)->GetCommandType()) {
      /*
    
        This is not official! Just testing to see Material, Texture, and Mesh work!!
      
      */
      case RenderCommandType::RENDER_MESH: {
        ExecuteMeshCommand(static_cast<MeshCommand *>((*it)));
      }
      break;
      case RenderCommandType::RENDER_GROUP: {
      }
      default:
      break;
    }
  }

  // Clear after.
  m_command_list.Clear();
  m_pointlights.Clear();
}


/**
  This will likely fall into it's own resources class. Needs to be handled by 
  Material.
*/
GLenum GLRenderer::GetDepthFunct(DepthFunc funct) {
  switch(funct) {
    case DepthFunc::vikr_DEPTH_ALWAYS: return GL_ALWAYS;
    case DepthFunc::vikr_DEPTH_EQUAL: return GL_EQUAL;
    case DepthFunc::vikr_DEPTH_GEQUAL: return GL_GEQUAL;
    case DepthFunc::vikr_DEPTH_GREATER: return GL_GREATER;
    case DepthFunc::vikr_DEPTH_LEQUAL: return GL_LEQUAL;
    case DepthFunc::vikr_DEPTH_LESS: return GL_LESS;
    case DepthFunc::vikr_DEPTH_NEVER: return GL_NEVER;
    case DepthFunc::vikr_DEPTH_NOTEQUAL: return GL_NOTEQUAL;
    default: return GL_LESS;
  }
}

/**
  These need to go into Material! Waste of time searching!
*/
GLenum GLRenderer::GetBlendFunct(BlendFunc blend) {
  switch (blend) {
    case BlendFunc::vikr_BLEND_CONSTANT_ALPHA: return GL_CONSTANT_ALPHA;
    case BlendFunc::vikr_BLEND_CONSTANT_COLOR: return GL_CONSTANT_COLOR;
    case BlendFunc::vikr_BLEND_DST_ALPHA: return GL_DST_ALPHA;
    case BlendFunc::vikr_BLEND_DST_COLOR: return GL_DST_COLOR;
    case BlendFunc::vikr_BLEND_GL_ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
    case BlendFunc::vikr_BLEND_ONE: return GL_ONE;
    case BlendFunc::vikr_BLEND_ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
    case BlendFunc::vikr_BLEND_ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC1_ALPHA;
    case BlendFunc::vikr_BLEND_ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunc::vikr_BLEND_SRC_ALPHA: return GL_SRC_ALPHA;
    case BlendFunc::vikr_BLEND_SRC_COLOR: return GL_SRC_COLOR;
    case BlendFunc::vikr_BLEND_ZERO: return GL_ZERO;
    default: return GL_ZERO;
  }
}


GLenum GLRenderer::GetFrontFace(FrontFace mode) {
  switch (mode) {
    case FrontFace::vikr_CLOCKWISE: return GL_CW;
    case FrontFace::vikr_COUNTER_CLOCKWISE: return GL_CCW;
    default: return GL_CCW;
  }
}


GLenum GLRenderer::GetCullFace(CullFace face) {
  switch (face) {
    case CullFace::vikr_FRONT_FACE: return GL_FRONT;
    case CullFace::vikr_BACK_FACE: return GL_BACK;
    default: return GL_BACK;
  }
}


vint32 GLRenderer::ExecuteMeshCommand(MeshCommand *mesh_cmd) {
  Material *material = mesh_cmd->GetMesh()->GetMaterial();
  if (material->HasDepth()) {
    GLEnable(GL_DEPTH_TEST);
    GLDepthFunc(GLRenderer::GetDepthFunct(material->GetDepthFunc()));
  } else {
    glDisable(GL_DEPTH_TEST);
  }
  if (material->IsCulling()) {
    glEnable(GL_CULL_FACE);
    GLFrontFace(GLRenderer::GetFrontFace(material->GetFrontFace()));
    GLCullFace(GLRenderer::GetCullFace(material->GetCullFace()));
  } else {
    GLDisable(GL_CULL_FACE);
  }
  if (material->IsBlending()) {
    GLEnable(GL_BLEND);
    GLBlendFunc(GLRenderer::GetBlendFunct(material->GetBlendSrc()), 
                GLRenderer::GetBlendFunct(material->GetBlendDst()));
  } else {
    GLDisable(GL_BLEND);
  }

  if(material) {
    Shader *shader = material->GetShader();
    shader->Use();
    shader->SetValue("vikr_view", camera->GetView());
    shader->SetValue("vikr_projection", camera->GetProjection());
    shader->SetValue("vikr_model", mesh_cmd->GetTransform());
    shader->SetValue("vikr_camPosition", glm::vec3(camera->GetPos().x, 
                                                   camera->GetPos().y, 
                                                   camera->GetPos().z));
    /*
        Algorithm to light a scene!
        1. Render Directional lights first
        2. Render Pointlights second
        3. Render Spotlights last!
    */ 
    std::vector<PointLight *>& pointlights = m_pointlights.GetCommandList();
    for (vuint32 i = 0; i < pointlights.size(); ++i) {
      std::string position = "light_pos";
      std::string ambient = "light_ambient";
      std::string diffuse = "light_diffuse";
      std::string specular = "light_specular";
      std::string constant = "constant";
      std::string linear = "linear";
      std::string quadratic = "quadratic";
      shader->SetValue("blinn", true);
      shader->SetValue(position, pointlights[i]->GetPos());
      shader->SetValue(ambient, glm::vec3(0.05f, 0.05f, 0.05f));
      shader->SetValue(diffuse, glm::vec3(0.8f, 0.8f, 0.8f));
      shader->SetValue(specular, glm::vec3(1.0f, 1.0f, 1.0f));
      shader->SetValue(constant, 1.0f);
      shader->SetValue(linear, 0.09f);
      shader->SetValue(quadratic, 0.032f);
    }
    /**
      Require multiple texture targets!
    */
    std::map<std::string, TextureSampler> *samplers = material->GetUniformSamplers();
    std::map<std::string, MaterialValue> *uniforms = material->GetMaterialValues();
    for (std::map<std::string, TextureSampler>::iterator it = samplers->begin();
         it != samplers->end(); ++it) {
      it->second.texture->Bind(it->second.i);
      
    }
    for (std::map<std::string, MaterialValue>::iterator it = uniforms->begin();
         it != uniforms->end(); ++it) {
      switch (it->second.type) {
        case vikr_INT:    shader->SetValue(it->first, it->second.m_integer); break;
        case vikr_FLOAT:  shader->SetValue(it->first, it->second.m_float); break;
        case vikr_DOUBLE: shader->SetValue(it->first, it->second.m_double); break;
        case vikr_BOOL:   shader->SetValue(it->first, it->second.m_bool); break;
        case vikr_VEC2:   shader->SetValue(it->first, it->second.m_vec2); break;
        case vikr_VEC3:   shader->SetValue(it->first, it->second.m_vec3); break;
        case vikr_VEC4:   shader->SetValue(it->first, it->second.m_vec4); break;
        case vikr_MAT2:   shader->SetValue(it->first, it->second.m_mat2); break;
        case vikr_MAT3:   shader->SetValue(it->first, it->second.m_mat3); break;
        case vikr_MAT4:   shader->SetValue(it->first, it->second.m_mat4); break;
        default:          shader->SetValue(it->first, it->second.m_integer); break;
      }
    }
    vuint32 vertices = mesh_cmd->GetMesh()->GetVertices().size();
    BindVertexArray(mesh_cmd->GetMesh()->GetVAO());
    switch (mesh_cmd->GetMesh()->GetMeshMode()) {
      case vikr_TRIANGLES: DrawArrays(GL_TRIANGLES, 0, vertices); break;
      case vikr_TRIANGLE_STRIP: DrawArrays(GL_TRIANGLE_STRIP, 0, vertices); break; 
      case vikr_TRIANGLE_FAN: DrawArrays(GL_TRIANGLE_FAN, 0, vertices); break;
      case vikr_TRIANGLE_STRIP_ADJACENCY : DrawArrays(GL_TRIANGLE_STRIP_ADJACENCY, 0, vertices); break;
    }
    BindVertexArray(0);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, "Mesh command rendered with unknown material!!");
  }


  return 1;
}
} // vikr