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
enum class CullFace {
  vikr_CLOCKWISE,
  vikr_COUNTER_CLOCKWISE
};


enum class FrontFace {
  vikr_FRONT_FACE,
  vikr_BACK_FACE,
};
} // vikr
#endif // __VIKR_CULLMODE_HPP 