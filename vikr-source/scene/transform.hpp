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
class Transform {
public:
  /**
    Position of the object in world space.
  */
  glm::vec3 Position    = glm::vec3(0.0f);
  /**
    Object scale.
  */
  glm::vec3 Scale       = glm::vec3(1.0f);
  /**
    Object rotation represented as a Quaternion.
  */
  glm::quat Rotation    = glm::quat();

  glm::mat4 GetTransform() { return m_transformMatrix; }
  /**
    Calculate our dear ol' tranform matrix.

      Algorithm:    ->>>    
        Tranform4x4 = Translation4x4 * Rotation4x4 * Scale4x4
  */
  vvoid CalculateTransform();

private:
  /**
    Transform matrix.
  */
  glm::mat4 m_transformMatrix;
};
} // vikr
#endif // __VIKR_TRANSFORM_HPP