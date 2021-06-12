#pragma once
#include "rwl/Drawables/Rect/RectComm.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"
#include <xcb/xcb.h>

namespace rwl::impl {
  /*
   * All code common between all Rect specializations that have a pointer to a
   * Pen in them lives here
   */
  template <typename T>
  class RectPtrComm: public RectComm<T> {
  public:
    using RectComm<T>::RectComm;
    using RectComm<T>::operator=;

    void drawIn(Window &win) {
      xcb_poly_rectangle(impl::core::conn, win.m_win, this->m_pen->m_pen, 1,
                         this->m_rect);
    }

    virtual ~RectPtrComm() {}
  };
} // namespace rwl::impl
