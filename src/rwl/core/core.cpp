#include "core.hpp"

namespace rwl {
#if RWL_PLATFORM == LINUX
  xcb_connection_t *core::c = ([] {
    xcb_connection_t *c = xcb_connect(nullptr, nullptr);

    if (int err = xcb_connection_has_error(c)) {
      printf("Couldn't create connection to X Server. Error Code: %d", err);
      exit(EXIT_FAILURE);
    }

    return c;
  })();
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