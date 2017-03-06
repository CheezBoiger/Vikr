//
// Copyright (c) Mario Garcia, Under the MIT License
//
#ifndef __VIKR_PHYDEVICE_HPP
#define __VIKR_PHYDEVICE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>


#include <vikr/graphics/graphics.hpp>

#include <vector>


namespace vikr {


/**
  Physical Device Singleton. Checks if this PC is compatible with 
  Vulkan API.

  TODO(Garcia): Take advantage of using multiple Physical Devices?
*/
class VKPhysicalDevice {
public:
  VKPhysicalDevice();
  /**
    Check for suitable devices with Vulkan.
  */  
  vvoid CheckSuitableDevices(VkInstance &instance);
  /**
    Select the best physical device to use.
  */
  vvoid SelectPhysicalDevice();

  /**
    Get the current physical device being used.
  */
  VkPhysicalDevice GetCurrentDevice() { return m_physicalDevice; }

  std::vector<const vchar *> &GetDeviceExtensions() { return device_ext; }
private:
  /**
    Rate our found devices.
  */
  vint32 RateDeviceCompatibility(VkPhysicalDevice &device);
  vbool IsSuitable(VkPhysicalDevice &device);

  vuint32 m_currentCount;
  std::vector<VkPhysicalDevice> m_foundDevices;
  vbool CheckDeviceExtensionSupport(VkPhysicalDevice &device); 
  /**
    Current Physical Device we are using.
  */
  VkPhysicalDevice m_physicalDevice;

  std::vector<const vchar *> device_ext;

};


/**
  Queue family search.
*/
class VKQueueFamily {
public:
  /**
    Simple check to see if queue family contains at least graphics commands. 
  */
  vbool IsComplete() { return gfrFamily >= 0 && prstFamily >= 0; }

  /**
    Find us a queue family for rendering.
  */
  static VKQueueFamily FindQueueFamilies(VkPhysicalDevice device);
  
  vint32 GetGFRFamily() { return gfrFamily; }
  vint32 GetPrstFamily() { return prstFamily; }

private:
  vint32 gfrFamily = -1;
  vint32 prstFamily = -1;
};
} // vikr
#endif // __VIKR_PHYDEVICE_HPP