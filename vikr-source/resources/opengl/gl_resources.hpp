//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_OPENGL_RESOURCES_HPP
#define __VIKR_OPENGL_RESOURCES_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace vikr {


class GLSLShader;


class GLResources {
public:

  static vint32 StoreShader(std::string name, GLSLShader *shader);
  static GLSLShader *GetShader(std::string name);

private:
  static std::unordered_map<std::string, 
            std::pair<std::string, std::unique_ptr<GLSLShader> > > shaders;
};
} // vikr
#endif // __VIKR_OPENGL_RESOURCES_HPP