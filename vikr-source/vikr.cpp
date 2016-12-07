#include <vikr.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


vint32 Cleanup() {
  VikrLog::DisplayMessage(VIKR_NOTIFY, "cleaning up resources and renderer...");
  vint32 result = 0;
  if (Renderer::GetRenderer() != nullptr) {
    Renderer *renderer = Renderer::GetRenderer();
    delete renderer;
    renderer = nullptr;
    result = 1;
  }
  return result;
}
} // vikr