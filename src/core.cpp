#include "rwl/core.hpp"
#include "rwl/Window/WinBase.hpp"
#include <cstdlib>

namespace rwl {
  namespace impl {
#if RWL_PLATFORM == LINUX
    xcb_connection_t *core::conn = ([] {
      xcb_connection_t *conn = xcb_connect(nullptr, nullptr);

      if (int err = xcb_connection_has_error(conn)) {
        impl::log<impl::LogLevel::Error>(
            "Core", "Failed to connect to X Server. Error code ", err);
        exit(EXIT_FAILURE);
      }

      impl::log("Core", "Connected to X Server.");

      return conn;
    })();
    xcb_screen_t *core::scr =
        xcb_setup_roots_iterator(xcb_get_setup(conn)).data;
#endif

    const WinBase makeRoot() {
      return WinBase(impl::core::scr->root, {0, rwl::Dim(width(), height())},
                     rwl::Color::Black);
    }
  } // namespace impl

  const impl::WinBase root = impl::makeRoot();

  void end() {
#if RWL_PLATFORM == LINUX
    xcb_disconnect(impl::core::conn);
    impl::log("Core", "Disconnected from X server.");
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

    impl::log("Core", "Entered loop.");

    while (!finished) {
      func(finished);
      update();
    }

    impl::log("Core", "Exiting loop.");

    end();
  }
} // namespace rwl