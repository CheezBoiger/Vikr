//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_DEPTHMODE_HPP
#define __VIKR_DEPTHMODE_HPP



namespace vikr {


enum class DepthCompare {
  vikr_DEPTH_ALWAYS,
  vikr_DEPTH_NEVER,
  vikr_DEPTH_LESS, // default
  vikr_DEPTH_EQUAL,
  vikr_DEPTH_LEQUAL,
  vikr_DEPTH_GREATER,
  vikr_DEPTH_NOTEQUAL,
  vikr_DEPTH_GEQUAL
};
} // vikr
#endif // __VIKR_DEPTHMODE_HPP