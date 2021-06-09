#pragma once
#include "rwl/Window.hpp"

namespace rwl::impl {
  class DrawableBase {
  public:
    virtual void drawIn(Window &win) = 0;
  };
} // namespace rwl::impl
