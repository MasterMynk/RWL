#pragma once
#include "rwl/Window/WinComm.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Window: public impl::WinComm {
  private:
    void create();
    const WinComm &m_parent;

  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const Pos &pos = {0, 0}, const Dim &dim = {640, 480},
           const Color &bgColor = Color::White,
           const impl::WinComm &parent = root);
    // Window(const Pos &pos, const Dim &dim, const Color &bgColor,
    //        const WinComm &parent);

    ~Window() override;
  };
} // namespace rwl
