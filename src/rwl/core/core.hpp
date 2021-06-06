#pragma once
#include <functional>
#include <xcb/xcb.h>

namespace rwl {
  class Color;
  class Window;
  enum class Measurement { Pixels = 0, Mm };

  struct core {
  private:
#if RWL_PLATFORM == LINUX
    static xcb_connection_t *conn; // This is the connection to the X Server.
    static xcb_screen_t *scr;
#endif

    core() = delete;

    friend Color;
    friend Window;

    friend void end();
    friend void update();
    friend uint8_t depth();
    friend uint16_t width(const Measurement &);
    friend uint16_t height(const Measurement &);

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
    friend xcb_screen_t *&getS();
    friend xcb_connection_t *&getC();
#endif
  };

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
  inline xcb_screen_t *&getS() { return core::scr; }
  inline xcb_connection_t *&getC() { return core::conn; }
#endif

  void loop(std::function<void(bool &finished)> func);

  inline void update() {
#if RWL_PLATFORM == LINUX
    xcb_flush(core::conn);
#endif
  }

  inline void end() {
#if RWL_PLATFORM == LINUX
    xcb_disconnect(core::conn);
#endif
  }

  inline uint8_t depth() {
#if RWL_PLATFORM == LINUX
    return core::scr->root_depth;
#endif
  }

  inline uint16_t width(const Measurement &m = Measurement::Pixels) {
    if (m == Measurement::Pixels)
#if RWL_PLATFORM == LINUX
      return core::scr->width_in_pixels;
    return core::scr->width_in_millimeters;
#endif
  }

  inline uint16_t height(const Measurement &m = Measurement::Pixels) {
    if (m == Measurement::Pixels)
#if RWL_PLATFORM == LINUX
      return core::scr->height_in_pixels;
    return core::scr->height_in_millimeters;
#endif
  }
} // namespace rwl