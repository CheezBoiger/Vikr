//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SHADOW_MAP_HPP
#define __VIKR_SHADOW_MAP_HPP


#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/shader/shader_program.hpp>
#include <vikr/shader/shader.hpp>

#include <vikr/graphics/command_buffer.hpp>

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>


namespace vikr {


/**
  ShadowMap implementation.
*/
class ShadowMap {
public:

  ShadowMap(ShaderProgram *program);

  
  vvoid Execute(CommandbufferList *list);

  

private:

  ShaderProgram *m_shadowProgram;
};
} // vikr
#endif // __VIKR_SHADOW_MAP_HPP