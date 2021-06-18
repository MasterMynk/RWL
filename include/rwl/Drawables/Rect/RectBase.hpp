#pragma once

#include "rwl/Drawables/Drawable.hpp"
#include <array>
#include <vector>

namespace rwl::impl {

  template <size_t Size>
  class RectBase: public Drawable {
  private:
  public:
    using value_type = std::array<PosDim, Size>;
  };

  template <>
  class RectBase<0>: public Drawable {
  public:
    using value_type = std::vector<PosDim>;
  };
} // namespace rwl::impl
