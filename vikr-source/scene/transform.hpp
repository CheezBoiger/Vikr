//
// Copright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TRANSFORM_HPP
#define __VIKR_TRANSFORM_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>


namespace vikr {


/**

  Transform container, holds all values that associate an object's
  position, rotation, and scale in the world coordinates.

*/
struct Transform {
  /**
    Position of the object in world space.
  */
  glm::vec3 Position;
  /**
    Object scale.
  */
  glm::vec3 Scale;
  /**
    Object rotation represented as a Quaternion.
  */
  glm::quat Rotation;
};
} // vikr
#endif // __VIKR_TRANSFORM_HPP