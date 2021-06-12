#pragma once

#include "rwl/Drawables/Rect/RectComm.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"

namespace rwl::impl {
  template <typename PenType>
  class RectPtrComm;

  /*
   * All specializations of Rect that contain either a reference to a Pen or a
   * Pen should inherit from this class as this contains all common code for
   * them.
   */
  template <typename PenType>
  class RectRefComm: public RectComm<PenType> {
  public:
    using RectComm<PenType>::RectComm;

    void drawIn(Window &win) {
      xcb_poly_rectangle(impl::core::conn, win.m_win, this->m_pen.m_pen, 1,
                         &this->m_rect);
    }

    /******************************* Operators *******************************/
    template <typename T>
    RectRefComm &operator=(const RectRefComm<T> &other) {
      this->m_rect = other.m_rect;
      this->m_pen = other.m_pen;
      return *this;
    }

    template <typename T>
    RectRefComm &operator=(RectRefComm<T> &&other) {
      this->m_rect = other.m_rect;
      this->m_pen = std::move(other.m_pen);
      return *this;
    }

    template <typename T>
    RectRefComm &operator=(const RectPtrComm<T> &other) {
      this->m_rect = other.m_rect;
      this->m_pen = *(other.m_pen);
      return *this;
    }

    template <typename T>
    RectRefComm &operator=(RectPtrComm<T> &&other) {
      this->m_rect = other.m_rect;
      this->m_pen = std::move(*(other.m_pen));
      return *this;
    }

    // These just forward the responsibility to RectComm (base class)
    void operator=(const Pos &newPos) { RectComm<PenType>::operator=(newPos); }
    void operator=(const Dim &newDim) { RectComm<PenType>::operator=(newDim); }
    void operator=(IsPen auto &&newPen) {
      Drawable<PenType>::operator=(std::forward<decltype(newPen)>(newPen));
    }

    template <typename PenType0>
    friend class RectPtrComm;
  };
} // namespace rwl::impl
