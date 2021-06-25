#pragma once
#include "rwl/Window/WinBase.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Window: public impl::WinBase {
  private:
    void create();
    const WinBase &m_parent;
    const uint16_t m_borderWidth;
    const Color m_borderColor;

  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const PosDim &posDim = {0, {640, 480}},
           const Color &bgColor = Color::White,
           const impl::WinBase &parent = root, const uint16_t &borderWidth = 1,
           const Color &borderColor = rwl::Color::Black);

    inline const WinBase &getParent() const { return m_parent; }
    inline const uint16_t &getBorderWidth() const { return m_borderWidth; }
    inline const Color &getBorderColor() const { return m_borderColor; }

    ~Window() override;
  };
} // namespace rwl
