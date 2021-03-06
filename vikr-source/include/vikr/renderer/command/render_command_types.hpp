//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_COMMAND_TYPES_HPP
#define __VIKR_RENDER_COMMAND_TYPES_HPP


namespace vikr {


/**
  Ensures the Commands are of the specified variable and not 
  of some other integer value.
*/
enum class RenderCommandType {
  COMMAND_CAMERA,
  COMMAND_MESH,
  COMMAND_LIGHT,
  COMMAND_PRIMITIVE,
  COMMAND_TRANSFORM,
  COMMAND_GROUP,
  COMMAND_MATERIAL,
  COMMAND_DEBUG
};
} // vikr
#endif // __VIKR_RENDER_COMMAND_TYPES_HPP