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

#include <vikr/shader/stb/stb_truetype.h>
#include <vikr/shader/shader_program.hpp>
#include <string>


namespace vikr {


unsigned char ttf_buffer[1<<20];
unsigned char temp_bitmap[512*512];
stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs.


FontPrinter::FontPrinter(ShaderProgram *shader, std::string projection_name,
  std::string color_n)
  : m_fontshader(shader)
  , proj_name(projection_name)
  , color_name(color_n)
{
  
}


vvoid FontPrinter::Println(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color)
{
  if (!m_renderDevice || !m_fontshader) {
    return;
  }
  RenderContext *ctx = m_renderDevice->GetContext();
  ctx->GetPipelineState()->SetShaderProgram(m_fontshader);
  Material mtl;
  ShaderUniformParams params;
  mtl.SetMat4(proj_name, projection);
  mtl.SetVector3fv(color_name, color);
  ctx->SetShaderUniforms(&params);
  //ctx->EnableBlendMode(true);
  ctx->EnableCullMode(false);
  ctx->SetTexture(m_texture->GetNativeId(), m_texture->GetNativeTarget(), 0);
  ctx->QueryVertexbuffer(m_mesh->GetVertexBuffer());
  /*for (auto it = text.begin(); it != text.end(); it++) {
    if ((*it) >= 32 && (*it) < 128) { 
      stbtt_aligned_quad q;
      stbtt_GetBakedQuad(cdata, 512, 512, (*it)-32, &x, &y, &q, 1);
      vreal32 texcoords[] = {
        q.s0, q.t0,
        q.s1, q.t0,
        q.s1, q.t1,
        q.s1, q.t1,
        q.s0, q.t0,
        q.s0, q.t0
      };
      m_mesh->GetVertexBuffer()->BufferSubData(sizeof(glm::vec3) * 2, sizeof(texcoords), texcoords);
    }
  }*/
  ctx->Draw(0, m_mesh->GetVertices().size);
  ctx->SetTexture(0, m_texture->GetNativeTarget(), 0);
  ctx->EnableBlendMode(false);
  ctx->EnableCullMode(true);
}


vvoid FontPrinter::Print(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color)
{
}


vvoid FontPrinter::Init(RenderDevice *device, std::string font) {
  if (!device) {
    return;
  }
  m_renderDevice = device;
  FILE *f = fopen(font.c_str(), "rb");
  if (!f) {
    VikrLog::DisplayMessage(VIKR_ERROR, "File could not open! Skipping Font Printer init.");
    return;
  }
  fread(ttf_buffer, 1, 1<<20, f);
  stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata);
  m_texture = device->GetResourceManager()->CreateTexture(
    TextureTarget::vikr_TEXTURE_2D,
    //"../../libs/models/nanosuit/glass_dif.png", 
    std::string((vchar *)temp_bitmap), 
    true
  );
  m_texture->SetFilterMin(TextureFilterMode::vikr_TEXTURE_LINEAR);
  //m_texture->SetFormat(TextureFormat::vikr_RED);
  m_texture->Finalize();
  fclose(f);

  Quad quad;
  m_mesh = device->GetResourceManager()->CreateMesh(quad.GetPositions(),
    quad.GetNormals(), quad.GetUVs());
  m_mesh->GetVertices().usage_type = vikr_DYNAMIC;
  m_mesh->Build(device);
}


vvoid FontPrinter::Reset(RenderDevice *device, std::string font)
{
  // nothing yet.
}
} // vikr