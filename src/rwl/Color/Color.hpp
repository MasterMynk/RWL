#pragma once
#include "rwl/core/core.hpp"

// TODO: Add support for other colors.

namespace rwl {
  class Window;

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
    Color(const ColorEnum &color);

    friend Window;
  };
} // namespace rwl
