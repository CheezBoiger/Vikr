//
// Copyright (c) Mario Garcia, Under the MIT License. 
//
#ifndef __VIKR_GUID_GENERATOR_HPP
#define __VIKR_GUID_GENERATOR_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

namespace vikr {

/**
  guid type in the form of a 64 bit long value maybe?
*/
typedef vuint64 guid_t;


/**
  GUID Generator generates an id for an associated object.
*/
class GUIDGenerator {
  /**
    The current guid type increment.
  */
  static guid_t current_guid;
public:

  static guid_t Generate();
};
} // vikr
#endif // __VIKR_GUID_GENERATOR_HPP