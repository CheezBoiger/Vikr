//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERER_HPP
#define __VIKR_RENDERER_HPP

#include <renderer/irenderer.hpp>
#include <shader/ishader.hpp>
#include <string>
#include <unordered_map>

namespace vikr {




/**
  Renderer resources to use with the Renderer.
*/
class Renderer {
public:

static void LoadShader(IRenderer *renderer, std::string shader_name, std::string fs, std::string vs);
static IShader *GetShader(std::string shader_name);

private:
  std::unordered_map<std::string, IShader*> shader_storage;
};
}
#endif // __VIKR_RENDERER_HPP