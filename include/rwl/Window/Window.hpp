#pragma once
#include "rwl/Window/WinComm.hpp"

namespace rwl {
  class Window: public impl::WinComm {
  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const Pos &pos = {0, 0}, const Dim &dim = {640, 480},
           const Color &bgColor = Color::White);

    ~Window() override;
  };
} // namespace rwl
