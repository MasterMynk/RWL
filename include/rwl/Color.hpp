#pragma once
#include "rwl/Log.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Pen;
  class Window;
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

    inline bool operator==(const Color &other) {
      return (this->m_color == other.m_color);
    }

#if RWL_DEBUG == 1
    inline const uint32_t &getCol() const { return m_color; }
#endif

    friend Pen;
    friend Window;
    friend impl::WinComm;
  };
} // namespace rwl
