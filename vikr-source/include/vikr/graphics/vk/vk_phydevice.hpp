//
// Copyright (c) Mario Garcia, Under the MIT License
//
#ifndef __VIKR_PHYDEVICE_HPP
#define __VIKR_PHYDEVICE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <vector>


namespace vikr {


/**
  Physical Device Singleton. Checks if this PC is compatible with 
  Vulkan API.

  TODO(Garcia): Take advantage of using multiple Physical Devices?
*/
class VKPhysicalDevice {
public:
  /**
    Check for suitable devices with Vulkan.
  */  
  static vvoid CheckSuitableDevices(VkInstance &instance);
  /**
    Select the best physical device to use.
  */
  static vvoid SelectPhysicalDevice();

  /**
    Get the current physical device being used.
  */
  static VkPhysicalDevice GetCurrentDevice() { return m_physicalDevice; }
private:
  /**
    Rate our found devices.
  */
  static vint32 RateDeviceCompatibility(VkPhysicalDevice &device);
  static vbool IsSuitable(VkPhysicalDevice &device);

  static vuint32 m_currentCount;
  static std::vector<VkPhysicalDevice> m_foundDevices;
  static vbool CheckDeviceExtensionSupport(VkPhysicalDevice &device); 
  /**
    Current Physical Device we are using.
  */
  static VkPhysicalDevice m_physicalDevice;

  static const std::vector<const vchar *> device_ext;

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