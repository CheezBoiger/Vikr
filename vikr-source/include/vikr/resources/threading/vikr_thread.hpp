//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_THREAD_HPP
#define __VIKR_THREAD_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>


#include <thread>
#include <utility>
#include <chrono>


namespace vikr {


/**
  Vikr thread wrapper.
*/
class VikrThread {
public:
  
  template<typename Function, 
           typename... Args>
  VikrThread(Function &&funct, Args &&...args) 
    : thr(std::thread(std::forward<Function>(funct),
        std::forward<Args>(args)...)) 
  { }

  VikrThread()
     { }

  ~VikrThread() { }

  VIKR_DEFAULT_MOVE_AND_ASSIGN(VikrThread);

  vvoid Detach() { thr.detach(); }

  vvoid Join() { thr.join(); }

  vbool IsJoinable() { thr.joinable(); } 

  /**
    Get Id of the thread..
  */
  std::thread::id GetId() { return thr.get_id(); }

private:

  /**
    Thread handle.
  */
  std::thread thr;
};
} // vikr
#endif // __VIKR_THREAD_HPP