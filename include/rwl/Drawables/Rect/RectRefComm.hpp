#pragma once

#include "rwl/Drawables/Rect/RectComm.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"

namespace rwl::impl {
  /*
   * All specializations of Rect that contain either a reference to a Pen or a
   * Pen should inherit from this class as this contains all common code for
   * them.
   */
  template <typename PenType>
  class RectRefComm: public RectComm<PenType> {
  public:
    using RectComm<PenType>::RectComm;
    using RectComm<PenType>::operator=;

    void drawIn(Window &win) {
      xcb_poly_rectangle(impl::core::conn, win.m_win, this->m_pen.m_pen, 1,
                         &this->m_rect);
    }

    virtual ~RectRefComm() {}
  };
} // namespace rwl::impl
