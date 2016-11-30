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
  vvoid PushBack(RenderCommand *command, RenderPass *target);
  /**
    Objects that are transparent, require sorting in a certain order after opaque objects.
  */
  vvoid Sort();
  /**
    Clean up the Render Queue.
  */
  vvoid Clear();

  std::vector<RenderCommand *> *GetCommandList(RenderPass *pass) { return &m_command_map[pass]; }
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

  std::vector<RenderCommand *> *GetPostbatchCommands() { return &postbatch_commands; }

protected:
  SortingCallback sorting_comparator;
  SortingCallback deferred_comparator;
  /**
    These commands are deferred.
  */
  std::vector<RenderCommand *> postbatch_commands;
  /**
    RenderPasses for specific defined RenderCommands.
  */
  std::unordered_map<RenderPass *, std::vector<RenderCommand *>> m_command_map;
};
} // vikr
#endif // __VIKR_RENDER_QUEUE_HPP