//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/font_printer.hpp>
#include <vikr/util/vikr_log.hpp>

#include <vikr/shader/shader.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/resources/resource_manager.hpp>

#include <vikr/shader/stb/stb_truetype.h>
#include <string>


namespace vikr {


unsigned char ttf_buffer[1<<20];
unsigned char temp_bitmap[512*512];
stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs.


FontPrinter::FontPrinter(Shader *shader, std::string projection_name)
  : m_fontshader(shader)
  , proj_name(projection_name)
{
  
}


vvoid FontPrinter::Println(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color)
{
}


vvoid FontPrinter::Print(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color)
{
}


vvoid FontPrinter::Init(RenderDevice *device, std::string font)
{
  fread(ttf_buffer, 1, 1<<20, fopen(font.c_str(), "rb"));
  stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata);
  m_texture = device->GetResourceManager()->CreateTexture(
    TextureTarget::vikr_TEXTURE_2D, 
    std::string((vchar *)temp_bitmap), 
    true
  );
  
}


vvoid FontPrinter::Reset(RenderDevice *device, std::string font)
{
}
} // vikr