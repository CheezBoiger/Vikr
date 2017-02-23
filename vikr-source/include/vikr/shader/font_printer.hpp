//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_FONT_PRINTER_HPP
#define __VIKR_FONT_PRINTER_HPP

#include <vikr/shader/shader.hpp>
#include <vikr/shader/texture.hpp>

#include <vikr/graphics/viewport.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace vikr {


class ShaderProgram;
class RenderDevice;
class Shader;
class Mesh;


/**
  Font Printer to use for your Renderer API.
*/
class FontPrinter {
public:
  /**
    Sets font shader.
  */
  FontPrinter(ShaderProgram *prgm = nullptr,
              std::string projection_name = "projection",
              std::string color_n = "textColor");

  vvoid Println(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color);
  vvoid Print(std::string text, vreal32 x, vreal32 y, vreal32 scale, glm::vec3 color);

  vvoid Init(RenderDevice *device, std::string font);
  
  vvoid Reset(RenderDevice *device, std::string font);


  vvoid SetShader(ShaderProgram *prgm) { m_fontshader = prgm; }

  /**
    Set the projection.
  */
  vvoid SetProjectionName(std::string name) { proj_name = name; }
  
  /**
    Viewport will change the projection.
  */
  vvoid SetViewport(Viewport viewport) { 
    m_viewport = viewport;
    projection = glm::ortho(
      static_cast<vint32>(viewport.win_x), 
      static_cast<vint32>(viewport.win_width), 
      static_cast<vint32>(viewport.win_y), 
      static_cast<vint32>(viewport.win_height));
  }

private:
  
  RenderDevice *m_renderDevice = nullptr;
  glm::mat4 projection;
  Mesh *m_mesh;

  /**
    Viewport reference.
  */
  Viewport m_viewport;

  /**
    Font shader.
  */
  ShaderProgram *m_fontshader = nullptr;
  std::string proj_name;
  std::string color_name;
};
} // vikr
#endif // __VIKR_FONT_PRINTER_HPP