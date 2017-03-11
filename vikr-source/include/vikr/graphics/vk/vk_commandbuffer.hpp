//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_COMMANDBUFFER_HPP
#define __VIKR_VK_COMMANDBUFFER_HPP


#include <vikr/graphics/command_buffer.hpp>

#include <vikr/graphics/vk/vk.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


/// Vulkan Commandbuffer wrapper. This is to abstract the 
/// vkCommandBuffer from the implementation of the renderer.
class VKCommandbuffer : public Commandbuffer {
public:

private:
  
};


} // vikr
#endif // __VIKR_VK_COMMANDBUFFER_HPP