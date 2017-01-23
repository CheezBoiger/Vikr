//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>
#include <iomanip>
#include <algorithm>


#define DISPLAY_CHECK(type, message) \
          case type: \
            if ((VikrLog::unsuppressed & type) == type) { \
              PRINT_MESSAGE(type, message); \
            } \
            break 
                                


namespace vikr {


char VikrLog::unsuppressed = 0xF;
std::vector<std::pair<VikrMessage, std::string>> VikrLog::history_log;

void VikrLog::DisplayMessage(VikrMessage type, std::string message) {
  switch (type) {
    DISPLAY_CHECK(VIKR_NORMAL, message);
    DISPLAY_CHECK(VIKR_WARNING, message);
    DISPLAY_CHECK(VIKR_ERROR, message);
    DISPLAY_CHECK(VIKR_NOTIFY, message);
    DISPLAY_CHECK(VIKR_RUNTIME_DEBUG, message);
    default:
      PRINT_MESSAGE(UNKNOWN, "Unknown message");
      break;
  };
  //if ((VikrLog::unsuppressed & VIKR_ERROR) == VIKR_ERROR) {
  //  VIKR_PRINT("Press any key to continue the program...");
  //  std::cin.ignore();
  //}
}


void VikrLog::Suppress(VikrMessage type) {
  if ((VikrLog::unsuppressed & type) == type) {
    VikrLog::unsuppressed ^= type;
  }
}


void VikrLog::UnSupress(VikrMessage type) {
  if ((VikrLog::unsuppressed & type) != type) {
    VikrLog::unsuppressed |= type;
  }
}


void VikrLog::Store(VikrMessage type, std::string message) {
  history_log.push_back(std::make_pair(type, message));
}


void VikrLog::Dump() {
  std::for_each(history_log.begin(), history_log.end(), [] (std::pair<VikrMessage, std::string>& log) -> void {
    VikrLog::DisplayMessage(log.first, log.second);
  });
}


void VikrLog::ClearHistory() {
  history_log.clear();
}
} // vikr