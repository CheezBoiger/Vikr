//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MATERIAL_HPP
#define __VIKR_MATERIAL_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/cullmode.hpp>
#include <unordered_map>

namespace vikr {


class Shader;


class Material {
public:


protected:
  Shader *shader; // weak ref
  vbool has_depth;
  vbool is_culling;
  vbool is_blending;
  CullMode m_cullmode;
  CullFace m_cullface;

}; 
} // vikr
#endif // __VIKR_MATERIAL_HPP