//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RESOURCES_HPP
#define __VIKR_RESOURCES_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <memory>

namespace vikr {


class Shader;


class ResourceManager {
public:
  ResourceManager(GraphicsPipeline pipe = vikr_OPENGL);

  virtual ~ResourceManager() { }

  virtual vint32 StoreShader(std::string name, Shader *shader) = 0;
  virtual Shader *GetShader(std::string name) = 0;

  static ResourceManager *GetResourceManager() { return resources.get(); }
  static vvoid SetResourceManager(ResourceManager *r) { resources.reset(r); }


private:

  GraphicsPipeline pipeline;

  static std::unique_ptr<ResourceManager> resources;

};
} // vikr
#endif // __VIKR_RESOURCES_HPP