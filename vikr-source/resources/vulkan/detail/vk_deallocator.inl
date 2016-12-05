//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
template<typename Resource>
VkDeallocator<Resource>::VkDeallocator()
  : VkDeallocator( [] (Resource, VkAllocationCallbacks *) -> vvoid { })
{
}


template<typename Resource>
VkDeallocator<Resource>::VkDeallocator(VkAllocationCallback deletef)
{
  deallocator_funct = [=] (Resource obj) { 
    deletef(obj, nullptr); 
  }
}


template<typename Resource>
VkDeallocator<Resource>::VkDeallocator(
  const VkDeallocator<VkInstance> &instance,
  VkInstanceAllocationCallback deletef)
{
  deallocator_funct = [&instance, deletef] (Resource obj) { 
    deletef(instance, obj, nullptr); 
  }
}


template<typename Resource>
VkDeallocator<Resource>::VkDeallocator(
  const VkDeallocator<VkDevice> &device,
  VkDeviceAllocationCallback deletef)
{
  deallocator_funct = [&device, deletef] (Resource obj) {
    deletef(device, obj, nullptr);
  }
}