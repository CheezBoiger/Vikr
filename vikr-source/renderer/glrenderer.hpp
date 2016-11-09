//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLRENDERER_HPP
#define __VIKR_GLRENDERER_HPP


#include <renderer/irenderer.hpp>


namespace vikr {


/**
  Renderer using OpenGL Graphics APIs.
*/
class GLRenderer : public IRenderer {
public:
  GLRenderer();
  ~GLRenderer();


  vvoid Render() override;
private:

};
} // vikr
#endif // __VIKR_GLRENDERER_HPP