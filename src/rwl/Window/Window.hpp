#pragma once
#include "rwl/Color/Color.hpp"
#include "rwl/Log.hpp"
#include "rwl/Vec2.hpp"
#include <xcb/xcb.h>

// TODO: Pos arg of constructor should actually change the pos of the window.
/* TODO: getDim and getPos should return the actual window dims and pos rather
         than pre-defined ones. */
// TODO: setDim and setPos should actually change the window's pos and dim
// TODO: fix hide() and hideNoUpdate()
// TODO: Create Something like a root window
// TODO: bgcolor of the window should be changeable.

namespace rwl {
  class Window {
  private:
#if RWL_PLATFORM == LINUX
    xcb_window_t m_win;
    Dim m_dim;
    Pos m_pos;
    Color m_bgColor;
#endif

  private:
    void createWin() const;

  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const Dim &dim = {640, 480}, const Pos &pos = {0, 0},
           const Color &bgColor = Color::White);

    Window &operator=(const Window &other);

    Window &show();
    Window &showNoUpdate();

    Window &hide();
    Window &hideNoUpdate();

    inline const Dim &getDim() const {
      impl::log("Returning Window Dimensions as ", m_dim);
      return m_dim;
    }
    inline const Pos &getPos() const {
      impl::log("Returning Window Position as ", m_pos);
      return m_pos;
    }

    inline Window &setDim(const Dim &other) {
      this->m_dim = other;
      impl::log("Set Window Dimensions to ", this->m_dim);
      return *this;
    }
    inline Window &setPos(const Pos &other) {
      this->m_pos = other;
      impl::log("Set Window Position to ", this->m_pos);
      return *this;
    }

    ~Window();
  };
} // namespace rwl
