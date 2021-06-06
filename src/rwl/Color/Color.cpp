#include "Color.hpp"

namespace rwl {
  Color::Color(const ColorEnum &color)
      : m_color(color == Black ? impl::core::scr->black_pixel
                               : impl::core::scr->white_pixel) {}
} // namespace rwl
