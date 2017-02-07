//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TPOOL_HPP
#define __VIKR_TPOOL_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <vikr/resources/threading/vikr_thread.hpp>
#include <vikr/resources/threading/vikr_conditional.hpp>
#include <vikr/resources/threading/vikr_mutex.hpp>

#include <vector>


namespace vikr {





/**
  Thread pool handle object. NOT DEAD POOL.
*/
class ThreadPool {
public:
  
  

private:

  std::vector<VikrThread> m_workers;
  
  vuint32 n_hardware_threads;  
};
} // vikr 
#endif // __VIKR_TPOOL_HPP