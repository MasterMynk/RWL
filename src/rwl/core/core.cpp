#include "core.hpp"
#include <cstdlib>
#include <stdio.h>

namespace rwl {
  namespace impl {
#if RWL_PLATFORM == LINUX
    xcb_connection_t *core::conn = ([] {
      xcb_connection_t *conn = xcb_connect(nullptr, nullptr);

      if (int err = xcb_connection_has_error(conn)) {
        printf("Couldn't create connection to X Server. Error Code: %d", err);
        exit(EXIT_FAILURE);
      }

      return conn;
    })();
    xcb_screen_t *core::scr =
        xcb_setup_roots_iterator(xcb_get_setup(conn)).data;
#endif
  } // namespace impl

  void end() {
#if RWL_PLATFORM == LINUX
    xcb_disconnect(impl::core::conn);
#endif
  }

  void update() {
#if RWL_PLATFORM == LINUX
    xcb_flush(impl::core::conn);
#endif
  }

  inline uint8_t depth() {
#if RWL_PLATFORM == LINUX
    return impl::core::scr->root_depth;
#endif
  }

  uint16_t width(const Measurement &m) {
    if (m == Measurement::Pixels)
#if RWL_PLATFORM == LINUX
      return impl::core::scr->width_in_pixels;
    return impl::core::scr->width_in_millimeters;
#endif
  }

  uint16_t height(const Measurement &m) {
    if (m == Measurement::Pixels)
#if RWL_PLATFORM == LINUX
      return impl::core::scr->height_in_pixels;
    return impl::core::scr->height_in_millimeters;
#endif
  }

  void loop(std::function<void(bool &finished)> func) {
    bool finished = false;

    while (!finished) {
      func(finished);
      update();
    }

    end();
  }
} // namespace rwl