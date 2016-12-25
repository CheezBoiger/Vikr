//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
template<typename Resource>
VkMemoryManager<Resource>::VkMemoryManager()
  : VkMemoryManager( [] (Resource, VkAllocationCallbacks *) -> vvoid { })
{
}


template<typename Resource>
VkMemoryManager<Resource>::VkMemoryManager(VkAllocationCallback deletef)
{
  deallocator_funct = [=] (Resource obj) { 
    deletef(obj, nullptr); 
  };
}


template<typename Resource>
VkMemoryManager<Resource>::VkMemoryManager(
  const VkMemoryManager<VkInstance> &instance,
  VkInstanceAllocationCallback deletef)
{
  deallocator_funct = [&instance, deletef] (Resource obj) { 
    deletef(instance, obj, nullptr); 
  };
}


template<typename Resource>
VkMemoryManager<Resource>::VkMemoryManager(
  const VkMemoryManager<VkDevice> &device,
  VkDeviceAllocationCallback deletef)
{
  deallocator_funct = [&device, deletef] (Resource obj) {
    deletef(device, obj, nullptr);
  };
}