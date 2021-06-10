#pragma once
#include "rwl/Log.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Pen;
  namespace impl {
    class WinComm;
  } // namespace impl

  class Color {
  private:
    uint32_t m_color;

  private:
    inline const char *const colorToStr() const {
      return this->m_color == Black ? "Black" : "White";
    }

  public:
    enum ColorEnum { Black = 0, White };

  public:
    Color(const ColorEnum &color = Black);

#if RWL_DEBUG == 1
    inline const uint32_t &getCol() const {
      impl::log<impl::LogLevel::NoImp>("Returning color as ", m_color);
      return m_color;
    }
#endif

    friend Pen;
    friend impl::WinComm;
  };
} // namespace rwl
