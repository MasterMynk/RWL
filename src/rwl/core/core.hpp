#pragma once
#include <functional>
#include <xcb/xcb.h>

namespace rwl {
  struct core {
  private:
#if RWL_PLATFORM == LINUX
    static xcb_connection_t *c;
    static xcb_screen_t *scr;
#endif

    core() = delete;

    friend void end();
    friend void update();

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
    friend xcb_connection_t *&getC();
    friend xcb_screen_t *&getS();
#endif
  };

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
  inline xcb_screen_t *&getS() { return core::scr; }
  inline xcb_connection_t *&getC() { return core::c; }
#endif

  void loop(std::function<void(bool &finished)> func);

  inline void update() {
#if RWL_PLATFORM == LINUX
    xcb_flush(core::c);
#endif
  }

  inline void end() {
#if RWL_PLATFORM == LINUX
    xcb_disconnect(core::c);
#endif
  }
} // namespace rwl