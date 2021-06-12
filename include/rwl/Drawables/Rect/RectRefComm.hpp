#pragma once

#include "rwl/Drawables/Rect/RectComm.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"

namespace rwl::impl {
  template <typename PenType>
  class RectPtrComm;

  // template <typename T, typename PenType>
  // concept IsRectPtrComm = IsType<RectPtrComm<PenType>, T>;

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

    // template <typename T>
    // RectRefComm &operator=(const RectPtrComm<T> &other) {
    //   this->m_rect = other.m_rect;
    //   this->m_pen = other.m_pen;
    //   return *this;
    // }

    // If none of the above overloads match the requirements, then see if the
    // base class has any alternatives.
    template <typename T>
    RectRefComm &operator=(T &&toForward) {
      RectComm<PenType>::operator=(std::forward<T>(toForward));
      return *this;
    }

    virtual ~RectRefComm() {}
  };
} // namespace rwl::impl
