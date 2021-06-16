#pragma once
#include "rwl/Log.hpp"
#include "rwl/PosDim.hpp"
#include "rwl/Vec2.hpp"
#include <functional>
#include <memory>
#include <xcb/xcb.h>

namespace rwl {
  class Pen;
  class Color;
  class Window;

  template <size_t Size>
  class Rect;

  enum class Measurement { Pixels = 0, Mm };

  namespace impl {
    struct core;
    class WinComm;

    const WinComm makeRoot();
  } // namespace impl

  void end();
  void update();
  uint8_t depth();
  void loop(std::function<void(bool &finished)> func);
  uint16_t width(const Measurement &m = Measurement::Pixels);
  uint16_t height(const Measurement &m = Measurement::Pixels);
  extern const impl::WinComm root;

  namespace impl {
    struct core {
    private:
#if RWL_PLATFORM == LINUX
      static xcb_connection_t *conn; // This is the connection to the X Server.
      static xcb_screen_t *scr;
#endif

      core() = delete;

      friend ::rwl::Pen;
      friend ::rwl::Color;
      friend ::rwl::Window;

      friend WinComm;

      template <size_t Size>
      friend class ::rwl::Rect;

      friend const WinComm makeRoot();

      friend void ::rwl::end();
      friend void ::rwl::update();
      friend uint8_t ::rwl::depth();
      friend uint16_t ::rwl::width(const Measurement &);
      friend uint16_t ::rwl::height(const Measurement &);

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
      friend xcb_screen_t *&getS();
      friend xcb_connection_t *&getC();
#endif
    };

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
    inline xcb_screen_t *&getS() {
      impl::log<impl::LogLevel::NoImp>("Returning scr.");
      return core::scr;
    }
    inline xcb_connection_t *&getC() {
      impl::log<impl::LogLevel::NoImp>("Returning the connection.");
      return core::conn;
    }
#endif
  } // namespace impl
} // namespace rwl