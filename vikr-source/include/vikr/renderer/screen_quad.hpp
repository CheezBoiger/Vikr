//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SCREEN_QUAD_HPP
#define __VIKR_SCREEN_QUAD_HPP

#include <vikr/graphics/viewport.hpp>
#include <vikr/graphics/render_target.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/math/shape/quad.hpp>

#include <vikr/graphics/render_device.hpp>

#include <vikr/renderer/command/primitive_command.hpp>
#include <vikr/graphics/command_buffer.hpp>


namespace vikr {


class ScreenQuad {
public:
  ScreenQuad();

  vvoid Init(RenderDevice *device);

  vvoid Execute();

  vvoid AdjustGaussianBlur(vuint32 value);
  vvoid AdjustGreyScale(vuint32 value);
  vvoid AdjustSharpen(vuint32 value);

private:
  RenderDevice *m_device = nullptr;
  CommandbufferList list;
  PrimitiveCommand command;
  Mesh *m_quad = nullptr;
};
} // vikr
#endif // __VIKR_SCREEN_QUAD_HPP