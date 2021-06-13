#pragma once
#include "rwl/Drawables/Rect/RectComm.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"
#include <xcb/xcb.h>

namespace rwl::impl {
  template <typename PenType>
  class RectRefComm;

  /*
   * All code common between all Rect specializations that have a pointer to a
   * Pen in them lives here
   */
  template <typename PenType>
  class RectPtrComm: public RectComm<PenType> {
  public:
    using RectComm<PenType>::RectComm;
    using RectComm<PenType>::operator=;

    void drawIn(Window &win) {
      xcb_poly_rectangle(impl::core::conn, win.m_win, this->m_pen->m_pen, 1,
                         &this->m_rect);
    }

    virtual ~RectPtrComm() {}

    /******************************* Operators *******************************/
    /******************************* Operator= *******************************/
    template <typename T>
    RectPtrComm &operator=(const RectRefComm<T> &other) {
      this->m_rect = other.m_rect;
      *(this->m_pen) = other.m_pen;
      return *this;
    }

    template <typename T>
    RectPtrComm &operator=(RectRefComm<T> &&other) {
      this->m_rect = other.m_rect;
      *(this->m_pen) = std::move(other.m_pen);
      return *this;
    }

    template <typename T>
    RectPtrComm &operator=(const RectPtrComm<T> &other) {
      this->m_rect = other.m_rect;
      *(this->m_pen) = *(other.m_pen);
      return *this;
    }

    template <typename T>
    RectPtrComm &operator=(RectPtrComm<T> &&other) {
      this->m_rect = other.m_rect;
      *(this->m_pen) = std::move(*(other.m_pen));
      return *this;
    }

    // These just forward the responsibility to RectComm (base class)
    void operator=(const Pos &newPos) { RectComm<PenType>::operator=(newPos); }
    void operator=(const Dim &newDim) { RectComm<PenType>::operator=(newDim); }
    void operator=(IsPen auto &&newPen) {
      Drawable<PenType>::operator=(std::forward<decltype(newPen)>(newPen));
    }

    template <typename PenType0>
    friend class RectRefComm;
  };
} // namespace rwl::impl
