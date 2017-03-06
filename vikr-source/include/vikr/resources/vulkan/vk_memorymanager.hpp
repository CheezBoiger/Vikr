//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VKDEALLOCATOR_HPP
#define __VIKR_VKDEALLOCATOR_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include<vikr/graphics/graphics.hpp>
#include <functional>


namespace vikr {


//
//
// Initializer function for Vulkan Render Pipeline.
//
//
typedef vvoid( *VkFunctInitializer)();


/**
  Vulkan Deallocation Memory management. It's a standard 
  Deallocator.
  Custom made interface.
*/
template<typename Resource>
class VkMemoryManager {
  // Oh the good ol' C function ;=;, much faster to do this way ;=;
  // We'll need to figure out how to speed up performance slightly.
  //typedef vvoid(*VkAllocationCallback)(Resource, VkAllocationCallbacks *);
  
  // Should we stick to this using keyword format?
  using VkAllocationCallback = 
    std::function<vvoid(Resource, 
      VkAllocationCallbacks *)>;
  
  using VkInstanceAllocationCallback = 
    std::function<vvoid(VkInstance, 
      Resource, 
      VkAllocationCallbacks *)>;

  using VkDeviceAllocationCallback = 
    std::function<vvoid(VkDevice, 
      Resource, 
      VkAllocationCallbacks *)>;
  
  using VkDeallocatorCallback = 
    std::function<vvoid(Resource)>;

public:

  VkMemoryManager(); 

  VkMemoryManager(VkAllocationCallback callback);

  VkMemoryManager(const VkMemoryManager<VkInstance> &instance,
    VkInstanceAllocationCallback deletef);

  VkMemoryManager(const VkMemoryManager<VkDevice> &device,
    VkDeviceAllocationCallback deletef);

  ~VkMemoryManager() { Cleanup(); }


  const Resource *operator &( ) const { return &obj; }

  Resource &Get() { return obj; }

  Resource *Replace() { Cleanup(); return &obj; }

  operator Resource() const { return obj; }

  vvoid operator=(Resource rhs) { 
    if (rhs != obj) {
      Cleanup();
      obj = rhs; 
    } 
  }

  template<typename Val>
  vbool operator=(Val rhs) {
    return obj == static_cast<Resource>(rhs);
  }
  

private:

  /**
  */
  Resource obj {VK_NULL_HANDLE};
  
  /**
    Deallocation function.
  */
  VkDeallocatorCallback deallocator_funct;

  vvoid Cleanup() {
    if (obj) {
      deallocator_funct(obj);
    }
    obj = VK_NULL_HANDLE;
  }
};

#include "detail/vk_memorymanager.inl"

} // vikr
#endif // __VIKR_VKDEALLOCATOR_HPP