//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/font_printer.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/math/shape/quad.hpp>
#include <vikr/renderer/renderer.hpp>
#include <vikr/scene/camera.hpp>
#include <vikr/shader/stb/stb_truetype.h>
#include <vikr/shader/shader_program.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>


namespace vikr {



struct Character {
  glm::ivec2 size;
  glm::ivec2 bearing;
  vuint32 advance;
  Texture *texture;
};


std::map<vchar, Character> characters;


FontPrinter::FontPrinter(ShaderProgram *shader, std::string projection_name,
  std::string color_n)
  : m_fontshader(shader)
  , proj_name(projection_name)
  , color_name(color_n)
  , m_mesh(nullptr)
{
  
}


vvoid FontPrinter::Println(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color)
{
  x = (x * 2) - m_viewport.win_width;
  y = (y * 2) - m_viewport.win_height;
  if (!m_renderDevice || !m_fontshader) {
    return;
  }
  RenderContext *ctx = m_renderDevice->GetContext();
  ctx->GetPipelineState()->SetShaderProgram(m_fontshader);
  ctx->GetPipelineState()->Update();
  Material mtl;
  ShaderUniformParams params;
  projection = glm::ortho(-1200.0f, 1200.f, -800.0f, 800.0f); // Hardcoded value!
  mtl.SetInt("text", 0);
  mtl.SetMat4(proj_name, projection);
  mtl.SetVector3fv(color_name, color);
  params.samplers = mtl.GetUniformSamplers();
  params.uniforms = mtl.GetMaterialValues();
  ctx->SetShaderUniforms(&params);
  ctx->EnableBlendMode(true);
  ctx->QueryVertexbuffer(m_mesh->GetVertexBuffer());
  for (std::string::const_iterator it = text.begin(); it != text.end(); it++) {
    Character &ch = characters[*it];
    vreal32 xpos = (x + ch.bearing.x * scale) / m_viewport.win_width;
    vreal32 ypos = (y - (ch.size.y - ch.bearing.y) * scale) / m_viewport.win_height;

    vreal32 w = (ch.size.x * scale) / m_viewport.win_width;
    vreal32 h = ch.size.y * scale / m_viewport.win_height;
    vreal32 vertices[] = {
            xpos,     ypos + h,   0.0,
            xpos,     ypos,       0.0,
            xpos + w, ypos,       0.0,

            xpos,     ypos + h,   0.0,
            xpos + w, ypos,       0.0, 
            xpos + w, ypos + h,   0.0,
      0.0, 0.0,
      0.0, 1.0,
      1.0, 1.0,
      0.0, 0.0,
      1.0, 1.0,
      1.0, 0.0
    };
    ctx->SetTexture(ch.texture->GetNativeId(), ch.texture->GetNativeTarget(), 0);
    m_mesh->GetVertexBuffer()->BufferSubData(0, sizeof(vertices), &vertices);
    ctx->Draw(0, m_mesh->GetVertices().positions.size() / 3);
    x += (ch.advance >> 6) * scale;
  }
  ctx->EnableBlendMode(false);
}


vvoid FontPrinter::Print(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color)
{
}


vvoid FontPrinter::Init(RenderDevice *device, std::string font) {
  if (!device) {
    return;
  }
  m_renderDevice = device;
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Freetype engine was not initialized!");
  }

  FT_Face face;
  if (FT_New_Face(ft, font.c_str(), 0, &face)) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Front engine did not generate!");
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  
  for (vbyte c = 0; c < 128; ++c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      VikrLog::DisplayMessage(VIKR_ERROR, "Unable to load glyph => " + c);
      continue;
    }
    Texture *texture = device->GetResourceManager()->CreateTexture(
      std::to_string(c),
      vikr_TEXTURE_2D,
      "",
      false);
    texture->SetByteCode(face->glyph->bitmap.buffer, false);
    texture->SetWidth(face->glyph->bitmap.width);
    texture->SetHeight(face->glyph->bitmap.rows);
    texture->SetWrapS(vikr_TEXTURE_CLAMP_TO_EDGE);
    texture->SetWrapT(vikr_TEXTURE_CLAMP_TO_EDGE);
    texture->SetFormat(vikr_RED);
    texture->SetInternalFormat(vikr_RED);
    texture->SetFilterMin(vikr_TEXTURE_LINEAR);
    texture->SetFilterMax(vikr_TEXTURE_LINEAR);
    texture->SetMipmapping(false);
    texture->Finalize();
    Character character = {
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      static_cast<vuint32>(face->glyph->advance.x),
      texture
    };
    characters.insert(std::pair<vchar, Character>(c, character));
  }
  // finished generating.
  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  Quad quad;
  if (!m_mesh) {
    m_mesh = device->GetResourceManager()->CreateMesh(
      quad.GetPositions(), std::vector<glm::vec3>(), quad.GetUVs());
    m_mesh->GetVertices().usage_type = vikr_DYNAMIC;  
    m_mesh->Build(device);
  }  


  Shader *vert_font = device->GetResourceManager()->CreateShader("vert_font", VERTEX_SHADER);
  vert_font->Compile("../../libs/shader/GLSL/font.vert");
  Shader *frag_font = device->GetResourceManager()->CreateShader("frag_font", PIXEL_SHADER);
  frag_font->Compile("../../libs/shader/GLSL/font.frag");

  m_fontshader = device->GetResourceManager()->CreateShaderProgram();
  m_fontshader->LoadShader(vert_font);
  m_fontshader->LoadShader(frag_font);
  m_fontshader->Build();

  device->GetResourceManager()->DestroyShader(vert_font->GetName());
  device->GetResourceManager()->DestroyShader(frag_font->GetName());
}


vvoid FontPrinter::Reset(RenderDevice *device, std::string font)
{
  // nothing yet.
}
} // vikr