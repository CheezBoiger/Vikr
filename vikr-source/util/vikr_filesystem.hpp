//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_FILESYSTEM_HPP
#define __VIKR_FILESYSTEM_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

#include <string>
#include <unordered_set>

namespace vikr {


/**
  Static Filesystem for use to handle directory structures and multiple 
  Filesystem heirarchies on Windows, Linux, and (maybe?) OS X. This is a  
  simple implementation for ease of use, especially with shader loading!
*/
class Filesystem {
public:

  // TODO(Garcia): Paths must be specified by the user, or the 
  // engine by default.
  static vbool IsDirectory(std::string path);

  static vbool IsFile(std::string filepath);

  static std::string CreateVikrDirectory(std::string filepath);

  static std::string GetVikrResourceDirectoryPath(std::string path);

  static std::string GetVikrDirectory(std::string path);

  static std::string SetVikrCurrentDirectory(std::string path);

  static std::string GetVikrCurrentDirectory();
};
} // vikr 
#endif // __VIKR_FILESYSTEM_HPP