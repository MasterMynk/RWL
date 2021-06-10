#pragma once
#include "rwl/Window/WinComm.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Window: public impl::WinComm {
  private:
    void create();
    const WinComm &m_parent;
    const uint16_t m_borderWidth;

  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const Pos &pos = {0, 0}, const Dim &dim = {640, 480},
           const Color &bgColor = Color::White,
           const impl::WinComm &parent = root, const uint16_t &borderWidth = 1);

    inline const WinComm &getParent() const { return m_parent; }
    inline const uint16_t &getBorderWidth() const { return m_borderWidth; }

    ~Window() override;
  };
} // namespace rwl
