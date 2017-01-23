//
// Copyright (c) Mario Garca, Under the MIT License.
//
#ifndef __VIKR_LOGGER_HPP
#define __VIKR_LOGGER_HPP

#include <iostream>
#include <string>
#include <vector>


#define MESSAGE_TYPE(type) #type
#define PRINT_MESSAGE(type, message) std::cout << #type << ": " << message << std::endl
#define VIKR_PRINT(stmt, ...) std::printf(stmt, ##__VA_ARGS__) 

namespace vikr {


enum VikrMessage {
  VIKR_NORMAL         = 0x1,
  VIKR_WARNING        = 0x2,
  VIKR_ERROR          = 0x4,
  VIKR_NOTIFY         = 0x8,
  VIKR_RUNTIME_DEBUG  = 0x10
};


/**
  VikrLog handles runtime message logging and history, in order to display onto the 
  renderer system of the notifications and whatnot that go on in the program. This 
  will not display the message to console, it just stores.
*/
class VikrLog {
public:
  /**
    Store the message into a logger to save the message history.
  */
  static void Store(VikrMessage type, std::string message);
  /**
    Dump all messages into the console, this will display everything that is stored in the
    message history.
  */
  static void Dump();
  /**
    Display a message onto the console without storing into history.
  */
  static void DisplayMessage(VikrMessage type, std::string message);
  /**
    Suppress messages that are displayed by the given type. This will suppress any
    messages of the given type. 
  */
  static void Suppress(VikrMessage type);
  /**
    Any message types that were previously suppressed, can be unsupressed to be displayed
    once again.
  */
  static void UnSupress(VikrMessage type);
  /**
    Clears all of the history in the log history queue.
  */
  static void ClearHistory();
private:
  static char unsuppressed;
  static std::vector<std::pair<VikrMessage, std::string>> history_log; 
};
} // vikr
#endif // __VIKR_LOGGER_HPP