#pragma once
#include "rwl/core/core.hpp"

// TODO: Add support for other colors.

namespace rwl {
  class Window;

  class Color {
  private:
    uint32_t m_color;

  public:
    enum ColorEnum { Black = 0, White };

  public:
    Color(const ColorEnum &color);

    friend Window;
  };
} // namespace rwl
