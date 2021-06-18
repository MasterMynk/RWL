#pragma once
#include "rwl/Window/WinComm.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Window: public impl::WinComm {
  private:
    void create();
    const WinComm &m_parent;
    const uint16_t m_borderWidth;
    const Color m_borderColor;

  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const PosDim &posDim = {0, {640, 480}},
           const Color &bgColor = Color::White,
           const impl::WinComm &parent = root, const uint16_t &borderWidth = 1,
           const Color &borderColor = rwl::Color::Black);

    inline const WinComm &getParent() const { return m_parent; }
    inline const uint16_t &getBorderWidth() const { return m_borderWidth; }
    inline const Color &getBorderColor() const { return m_borderColor; }

    ~Window() override;
  };
} // namespace rwl
