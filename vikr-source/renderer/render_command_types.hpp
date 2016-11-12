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
  RENDER_MESH,
  RENDER_GROUP,
  RENDER_PRIMITIVE,
  RENDER_TRIANGLES
};
} // vikr
#endif // __VIKR_RENDER_COMMAND_TYPES_HPP