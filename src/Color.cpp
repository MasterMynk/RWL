#include "rwl/Color.hpp"
#include "rwl/Log.hpp"

namespace rwl {
  Color::Color(const ColorEnum &color)
      : m_color(color == Black ? impl::core::scr->black_pixel
                               : impl::core::scr->white_pixel) {
    impl::log("Created a Color with color ", colorToStr());
  }
} // namespace rwl
