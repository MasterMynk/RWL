#pragma once
#include "rwl/Log.hpp"
#include <functional>
#include <memory>
#include <xcb/xcb.h>

namespace rwl {
  class Pen;
  class Color;
  class Window;

  enum class Measurement { Pixels = 0, Mm };

  namespace impl {
    struct core;
  }

  void end();
  void update();
  uint8_t depth();
  void loop(std::function<void(bool &finished)> func);
  uint16_t width(const Measurement &m = Measurement::Pixels);
  uint16_t height(const Measurement &m = Measurement::Pixels);

  namespace impl {
    template <typename T>
    class RectPtrComm;

    template <typename T>
    class RectRefComm;

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

      template <typename T>
      friend class RectPtrComm;

      template <typename T>
      friend class RectRefComm;

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