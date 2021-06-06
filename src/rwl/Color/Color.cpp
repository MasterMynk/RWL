#include "Color.hpp"

namespace rwl {
  Color::Color(const ColorEnum &color)
      : m_color(color == Black ? core::scr->black_pixel
                               : core::scr->white_pixel) {}
} // namespace rwl
