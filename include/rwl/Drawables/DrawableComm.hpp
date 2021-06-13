#pragma once
#include "rwl/Window/Window.hpp"

namespace rwl::impl {
  class DrawableComm { // Comm is for common.
    // All common code between all Drawable specializations lives here
  public:
    virtual void drawIn(Window &win) = 0;
  };
} // namespace rwl::impl
