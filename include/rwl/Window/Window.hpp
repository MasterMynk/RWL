#pragma once
#include "rwl/Window/WinBase.hpp"
#include "rwl/core.hpp"

namespace rwl {
  class Window: public impl::WinBase {
  private:
    const WinBase &m_parent;
    const uint16_t m_borderWidth;
    const Color m_borderColor;

  private:
    /****************************** Helper Ctors ******************************/
    Window(const xcb_window_t &win, const PosDim &pd, const Color &bg,
           const impl::WinBase &parent, const uint16_t &borderWidth,
           const Color &borderColor);

    /******************************** Helpers ********************************/
    void create();

  public:
    enum class Visibility { Show, Hide };

  public:
    /********************************* Ctors *********************************/
    explicit Window(Window &&other);
    explicit Window(const Window &other);

    template <Visibility v = Visibility::Show>
    Window(const PosDim &posDim = {0, {640, 480}},
           const Color &bgColor = Color::White,
           const impl::WinBase &parent = root, const uint16_t &borderWidth = 1,
           const Color &borderColor = rwl::Color::Black)
        : Window(xcb_generate_id(impl::core::conn), posDim, bgColor, parent,
                 borderWidth, borderColor) {
      this->create();

      if constexpr (v == Visibility::Show)
        this->show();
    }

    /******************************** Getters ********************************/
    inline const WinBase &getParent() const { return m_parent; }
    inline const uint16_t &getBorderWidth() const { return m_borderWidth; }
    inline const Color &getBorderColor() const { return m_borderColor; }

    ~Window();
  };
} // namespace rwl
