//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDER_QUEUE_HPP
#define __VIKR_RENDER_QUEUE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>


namespace vikr {


class RenderCommand;
class RenderTarget;
class RenderPass;

/**
  Sorting callback.
*/
typedef vint32 (*SortingCallback)(RenderCommand *, RenderCommand *);


/**
  Custom RenderQueue for the Renderer.
*/
class RenderQueue {
public:
  vvoid PushBack(RenderCommand *command);
  vvoid PushBackDeferred(RenderCommand *command) {
    deferred_commands.push_back(command);
  }
  /**
    Objects that are transparent, require sorting in a certain order after opaque objects.
  */
  vvoid Sort();
  /**
    Clean up the Render Queue.
  */
  vvoid Clear();

  std::vector<RenderCommand *> &GetCommandBuffer() { return m_commandBuffer; }
  /**
    Registers a custom comparator for the render queue.
  */
  vvoid RegisterBatchComparator(SortingCallback func) 
    { sorting_comparator = func; }
  /**
    Registers a custom comparator for deferred commands. 
  */
  vvoid RegisterDeferredComparator(SortingCallback func) 
    { deferred_comparator = func; }

  std::vector<RenderCommand *> &GetDeferredCommands() { return deferred_commands; }

protected:
  SortingCallback sorting_comparator;
  SortingCallback deferred_comparator;
  /**
    These commands are deferred.
  */
  std::vector<RenderCommand *> deferred_commands;

  /**
    These commands are to be executed immediately.
  */
  std::vector<RenderCommand *> m_commandBuffer;
};
} // vikr
#endif // __VIKR_RENDER_QUEUE_HPP