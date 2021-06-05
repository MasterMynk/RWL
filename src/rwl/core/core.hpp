#pragma once
#include <functional>
#include <xcb/xcb.h>

// TODO: Add funcs to access details of the screen.

namespace rwl {
  class Window;

  struct core {
  private:
#if RWL_PLATFORM == LINUX
    static xcb_connection_t *conn; // This is the connection to the X Server.
    static xcb_screen_t *scr;
#endif

    core() = delete;

    friend Window;

    friend void end();
    friend void update();

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
} // namespace rwl