//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/vk/vk_commandbuffer.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


vvoid VKCommandbuffer::BeginRecord()
{
  if (recording) {
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, R"Cmd(
      Commandbuffer is already recording! Skipping call...
    )Cmd");
    return;
  }
  VkCommandBufferBeginInfo cmdBufferBeginInfo = { };
  cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  cmdBufferBeginInfo.pNext = nullptr;
  cmdBufferBeginInfo.pInheritanceInfo = nullptr;
  cmdBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  VkResult result = vkBeginCommandBuffer(m_commandbuffer, &cmdBufferBeginInfo);
  
  if (result != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Commandbuffer failed to begin!");
    return;
  }
  recording = true;
}


vvoid VKCommandbuffer::EndRecord()
{
  if (!recording) {
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, R"Cmd(
      This Commandbuffer was not Recording prior to calling EndRecord()!
      Skipping this call...
    )Cmd");
    return;
  }
  VkResult result = vkEndCommandBuffer(m_commandbuffer);
  if (result != VK_SUCCESS) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Unsuccessful End call of commandbuffer.");
    return;
  }
  recording = false;
}
} // vikr