//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <resources/resource_manager.hpp>


namespace vikr {


std::unique_ptr<ResourceManager> ResourceManager::resources = nullptr;


ResourceManager::ResourceManager(GraphicsPipeline pipe)
  : pipeline(pipe)
{
}
} // vikr