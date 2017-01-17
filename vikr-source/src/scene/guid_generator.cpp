//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/scene/guid_generator.hpp>


namespace vikr {


guid_t GUIDGenerator::current_guid = 0;


guid_t GUIDGenerator::Generate() {
  // Increment the current guid value for every generation.
  return current_guid++;
}
} // vikr 