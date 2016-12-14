//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_CUBEMAP_HPP
#define __VIKR_CUBEMAP_HPP


#include <shader/texture.hpp>
#include <memory>


namespace vikr {


/**
  Render a cubemap 
*/
class Cubemap {
public:
  Cubemap() { }
  virtual ~Cubemap() { }

  virtual vvoid Generate(std::vector<const vchar *> faces = std::vector<const vchar *>()) = 0;

  vuint32 GetTextureId() { return m_id; }

  vuint32 GetWidth() { return m_width; }
  vuint32 GetHeight() { return m_height; }  

protected:
  std::vector<const vchar *> m_faces; 
  vuint32 m_id;

  vuint32 m_width                       = 0;
  vuint32 m_height                      = 0;
};
} // vikr
#endif // __VIKR_CUBEMAP_HPP