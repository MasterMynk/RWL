#pragma once
#include "rwl/Vec2.hpp"
#include <xcb/xcb.h>

// TODO: Pos arg of constructor should actually change the pos of the window.
/* TODO: getDim and getPos should return the actual window dims and pos rather
         than pre-defined ones. */
// TODO: setDim and setPos should actually change the window's pos and dim
// TODO: fix hide() and hideNoUpdate()
// TODO: Create Something like a root window

namespace rwl {
  class Window {
  private:
#if RWL_PLATFORM == LINUX
    xcb_window_t m_win;
    Dim m_dim;
    Pos m_pos;
#endif

  private:
    void createWin() const;

  public:
    Window(Window &&other);
    Window(const Window &other);
    Window(const Dim &dim = {640, 480}, const Pos &pos = {0, 0});

    Window &operator=(const Window &other);

    Window &show();
    Window &showNoUpdate();

    Window &hide();
    Window &hideNoUpdate();

    inline const Dim &getDim() const { return m_dim; }
    inline const Pos &getPos() const { return m_pos; }

    inline Window &setDim(const Dim &other) {
      this->m_dim = other;
      return *this;
    }
    inline Window &setPos(const Pos &other) {
      this->m_pos = other;
      return *this;
    }

    ~Window();
  };
} // namespace rwl
