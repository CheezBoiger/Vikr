//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_CULLMODE_HPP
#define __VIKR_CULLMODE_HPP


namespace vikr {


/**
  State the Cull mode of the artifact, from which to 
  determine a front-facing or back-facing object.
*/
enum class CullMode {
  vikr_CLOCKWISE,
  vikr_COUNTER_CLOCKWISE
};
} // vikr
#endif // __VIKR_CULLMODE_HPP 