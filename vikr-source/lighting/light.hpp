//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_LIGHT_HPP
#define __VIKR_LIGHT_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <glm/glm.hpp>


namespace vikr {


class Mesh;


enum LightType {
  vikr_DIRECTIONLIGHT,
  vikr_POINTLIGHT,
  vikr_SPOTLIGHT
};


/**
  Light Abstract. Contains common variables to emit light.
*/
class Light {
public:
  Light() { }
  Light(LightType light_type,
        glm::vec3 position, 
        glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f)) 
    : m_position(position)
    , m_ambient(ambient)
    , m_diffuse(diffuse)
    , m_specular(specular) 
    , type(light_type) { }

  virtual ~Light() { }

  /**
    Set the position of the light.
  */
  vvoid SetPos(glm::vec3 position) { m_position = position; }
  /**
    Set the light ambients (the color at it's most darkest).
  */
  vvoid SetAmbient(glm::vec3 ambient) { m_ambient = ambient; }
  /**
    Set the light's diffuse (the color at it's most brightest).
  */
  vvoid SetDiffuse(glm::vec3 diffuse) { m_diffuse = diffuse; }
  /**
    Set the light's specular (the highlights of the light, think of it
    as when light hits directly to the camera eye).
  */
  vvoid SetSpecular(glm::vec3 specular) { m_specular = specular; }
  /**
    Color of the actual light entity.
  */
  vvoid SetColor(glm::vec3 color) { m_color = color; }

  glm::vec3 GetPos() { return m_position; } 
  glm::vec3 GetAmbient() { return m_ambient; }
  glm::vec3 GetDiffuse() { return m_diffuse; }
  glm::vec3 GetSpecular() { return m_specular; }
  glm::vec3 GetColor() { return m_color; }
  LightType GetLightType() { return type; }
  
protected:
  /**
    Get the light type.
  */
  LightType type;
  glm::vec3 m_position;
  /**
    Color when at it's most darkest.
  */
  glm::vec3 m_ambient;
  /**
    Color when at it's most brightest.
  */
  glm::vec3 m_diffuse;
  /**
    The Light's highlights, when it shines directly.
  */
  glm::vec3 m_specular;
  /**
    Color to depict for the Mesh object.
  */
  glm::vec3 m_color       = glm::vec3(1.0f, 1.0f, 1.0f);
};
}
#endif // __VIKR_LIGHT_HPP