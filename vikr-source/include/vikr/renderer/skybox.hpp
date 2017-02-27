//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_SKYBOX_HPP
#define __VIKR_SKYBOX_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/shader_program.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/renderer/command/primitive_command.hpp>
#include <vikr/renderer/command/camera_command.hpp>
#include <vikr/graphics/render_device.hpp>


namespace vikr {


class Skybox {
public:
  Skybox();

  vvoid Init(RenderDevice *device);

  Cubemap *GetCubemap() { return cubemap; }

  vvoid Execute();

private:
  RenderDevice *m_device;
  CommandbufferList *list;
  PrimitiveCommand sky_cmd;
  CameraCommand cam_cmd;
  ShaderProgram *program;

  Mesh *skybox;  
  Cubemap *cubemap;
  std::vector <const vchar *> skybox_input;
};
} // vikr
#endif // __VIKR_SKYBOX_HPP