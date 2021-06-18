#pragma once
#include "rwl/Pen.hpp"
#include "rwl/Window/Window.hpp"

namespace rwl {
  class Drawable {
  public:
    virtual void draw(Window &win, const Pen &pen) = 0;
  };
} // namespace rwl
