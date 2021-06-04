#include "core.hpp"

namespace rwl {
#if RWL_PLATFORM == LINUX
  xcb_connection_t *core::c = xcb_connect(nullptr, nullptr);
  xcb_screen_t *core::scr = xcb_setup_roots_iterator(xcb_get_setup(c)).data;
#endif

  void loop(std::function<void(bool &finished)> func) {
    bool finished = false;

    while (!finished) {
      func(finished);
      update();
    }

    end();
  }
} // namespace rwl