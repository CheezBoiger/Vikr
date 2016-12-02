//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <renderer/opengl/glrenderer.hpp>
#include <renderer/renderer.hpp>
#include <renderer/render_command.hpp>
#include <renderer/mesh_command.hpp>
#include <renderer/primitive_command.hpp>
#include <renderer/opengl/gl_rendertarget.hpp>
#include <renderer/pass.hpp>

#include <shader/material.hpp>
#include <shader/stb/stb_image.h>
#include <shader/glsl/glsl_shader.hpp>
#include <shader/glsl/gl_texture.hpp>
#include <shader/glsl/gl_texture1d.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <shader/glsl/gl_texture3d.hpp>

#include <mesh/opengl/glmesh.hpp>

#include <scene/camera.hpp>

#include <util/vikr_log.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <lighting/point_light.hpp>
#include <lighting/light.hpp>

#include <resources/opengl/gl_resource_manager.hpp>


namespace vikr {


GLRenderer::GLRenderer()
  : Renderer(vikr_OPENGL)
{
}


vint32 GLRenderer::Init() {
  GLResourceManager *resource_manager = new GLResourceManager();
  ResourceManager::SetResourceManager(resource_manager);
  // I don't like dynamically allocated meshes.  -__-
  Quad q;
  quad = std::make_unique<GLMesh>();
  quad->Buffer(q.GetPositions(), q.GetNormals(), q.GetUVs());
  quad->Create();
  StoreShader("screen_shader", "screen_shader.vert", "screen_shader.frag");
  /**
    Wait WTF?!?!
  */
  m_render_queue.RegisterBatchComparator([] (RenderCommand *, RenderCommand *) -> vint32 {
    return 0;
  });

  m_render_queue.RegisterDeferredComparator([] (RenderCommand *, RenderCommand *) -> vint32 {
    return 0;
  });
  // Create default rendertarget.
  default_rendertarget = std::make_unique<GLRenderTarget>();
  default_rendertarget->SetWidth(1200);
  default_rendertarget->SetHeight(800);
  default_rendertarget->Generate();
  default_rendertarget->BindTexture(0);
  default_rendertarget->BindDepthStencil();
  default_rendertarget->IsComplete();
  default_rendertarget->Unbind();
  default_renderpass.Rendertargets.push_back(default_rendertarget.get());
  default_renderpass.Viewport.win_x = 0;
  default_renderpass.Viewport.win_y = 0;
  current_renderpass = &default_renderpass;
  m_renderpasses.push_back(&default_renderpass);
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
    return ResourceManager::GetResourceManager()->StoreShader(shader_name, &shader);
  }
  return -1;
}


Shader *GLRenderer::GetShader(std::string shader_name) {
  return ResourceManager::GetResourceManager()->GetShader(shader_name);
}


Texture *GLRenderer::CreateTexture(TextureTarget target, std::string img_path, vbool alpha) {
  Texture *texture = nullptr;
  vint32 width = 0;
  vint32 height = 0;
  vint32 depth = 0;
  vbyte *bytecode = stbi_load(img_path.c_str(), &width, &height, &depth,
                              alpha ? STBI_rgb_alpha : STBI_rgb);
  switch (target) {
    case vikr_TEXTURE_1D: texture = new GLTexture1D(width); break;
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
  vuint32 original_window_width = camera->GetViewport().win_width;
  vuint32 original_window_height = camera->GetViewport().win_height;
  default_renderpass.Viewport.win_width = original_window_width;
  default_renderpass.Viewport.win_height = original_window_height;
  vreal32 aspect = camera->GetAspect();

  rendering = true;
  ClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);  
  ClearDisplay(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Sort out the m_renderqueue
  Sort();
  // Perform drawing, need to better understand passes for rendering,
  // Pre-batch, batch, and Post-batch drawing.
  for (RenderPass *pass : m_renderpasses) {
    std::vector<RenderCommand *> &commands = *m_render_queue.GetCommandList(pass);
    Viewport  *viewport = &pass->Viewport;
    glViewport(viewport->win_x, viewport->win_y, viewport->win_width, viewport->win_height);
    for (RenderTarget *target : pass->Rendertargets) {
      target->Bind();
      glm::vec3 cc = target->GetClearColor();
      if (target->HasDepthAndStencil()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      } else {
        glClear(GL_COLOR_BUFFER_BIT);
      }
      glClearColor(cc.x, cc.y, cc.z, 1.0f);
      for (RenderCommand *command : commands) {
        switch (command->GetCommandType()) {
          case RenderCommandType::RENDER_MESH: { 
            ExecuteMeshCommand(static_cast<MeshCommand *>(command)); 
          } break;
          case RenderCommandType::RENDER_GROUP: break;
          case RenderCommandType::RENDER_PRIMITIVE: {
            ExecutePrimitiveCommand(static_cast<PrimitiveCommand *>(command));
          } 
          break;
          default: break;
        }
      }
    }
  }
  // Remove framebuffers.
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  // TODO(Garcia): Perform Blit and Post processing later on
  
  // Final render onto Quad.
  glViewport(0, 0, original_window_width, original_window_height);
  glClear(GL_COLOR_BUFFER_BIT);
  MeshCommand quadCommand;
  Material material(GLResourceManager::GetResourceManager()->GetShader("screen_shader"));
  material.SetDepth(false);
  material.SetIsCulling(false);
  material.SetTexture("screenTexture", default_rendertarget->GetTexture(), 0);
  quadCommand.SetMesh(quad.get());
  quadCommand.SetMaterial(&material);
  ExecuteMeshCommand(&quadCommand);
  // Restore.
  // Clear after.
  m_render_queue.Clear();
  m_pointlights.clear();
  rendering = false;
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
  Material *material = mesh_cmd->GetMaterial();
  SetGLContext(material);

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
    for (vuint32 i = 0; i < m_pointlights.size(); ++i) {
      std::string position = "light_pos";
      std::string ambient = "light_ambient";
      std::string diffuse = "light_diffuse";
      std::string specular = "light_specular";
      std::string constant = "constant";
      std::string linear = "linear";
      std::string quadratic = "quadratic";
      shader->SetValue("blinn", true);
      shader->SetValue(position,  m_pointlights[i]->GetPos());
      shader->SetValue(ambient,   m_pointlights[i]->GetAmbient());
      shader->SetValue(diffuse,   m_pointlights[i]->GetDiffuse());
      shader->SetValue(specular,  m_pointlights[i]->GetSpecular());
      shader->SetValue(constant,  m_pointlights[i]->GetConstant());
      shader->SetValue(linear,    m_pointlights[i]->GetLinear());
      shader->SetValue(quadratic, m_pointlights[i]->GetQuadratic());
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
    //BindVertexArray(0);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, "Mesh command rendered with unknown material!!");
  }


  return 1;
}


vint32 GLRenderer::ExecutePrimitiveCommand(PrimitiveCommand * command) {
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(command->GetLineWidth());
  BindVertexArray(command->GetMesh()->GetVAO());
  glDrawArrays(GL_LINES, 0, command->GetMesh()->GetVertices().size());
  glLineWidth(1);
  glDisable(GL_LINE_SMOOTH);
  return 1;
}


vvoid GLRenderer::SetGLContext(Material *material) {
  if(material->HasDepth()) {
    GLEnable(GL_DEPTH_TEST);
    GLDepthFunc(GLRenderer::GetDepthFunct(material->GetDepthFunc()));
  } else {
    glDisable(GL_DEPTH_TEST);
  }
  if(material->IsCulling()) {
    glEnable(GL_CULL_FACE);
    GLFrontFace(GLRenderer::GetFrontFace(material->GetFrontFace()));
    GLCullFace(GLRenderer::GetCullFace(material->GetCullFace()));
  } else {
    GLDisable(GL_CULL_FACE);
  }
  if(material->IsBlending()) {
    GLEnable(GL_BLEND);
    GLBlendFunc(GLRenderer::GetBlendFunct(material->GetBlendSrc()),
                GLRenderer::GetBlendFunct(material->GetBlendDst()));
  } else {
    GLDisable(GL_BLEND);
  }
}
} // vikr