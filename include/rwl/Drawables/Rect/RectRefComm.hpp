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
    /******************************* Operator= *******************************/
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
    inline void operator=(const Pos &newPos) {
      RectComm<PenType>::operator=(newPos);
    }
    inline void operator=(const Dim &newDim) {
      RectComm<PenType>::operator=(newDim);
    }
    inline void operator=(IsPen auto &&newPen) {
      Drawable<PenType>::operator=(std::forward<decltype(newPen)>(newPen));
    }

    /************************* Comparision Operators *************************/
    template <typename T>
    bool operator==(const RectRefComm<T> &other) {
      return (RectComm<PenType>::operator=(other.m_rect) &&
              this->m_pen == other.m_pen);
    }

    template <typename T>
    bool operator==(const RectPtrComm<T> &other) {
      return (RectComm<PenType>::operator=(other.m_rect) &&
              this->m_pen == *(other.m_pen));
    }

    // As the above override the base class's operator==, we have to declare it
    // again and tell it to use the RectComm's operator==.
    inline bool operator==(const Pos &otherPos) {
      return RectComm<PenType>::operator==(otherPos);
    }
    inline bool operator==(const Dim &otherDim) {
      return RectComm<PenType>::operator==(otherDim);
    }
    inline bool operator==(const Pen &otherPen) {
      return RectComm<PenType>::operator==(otherPen);
    }

    template <typename PenType0>
    friend class RectPtrComm;
  };
} // namespace rwl::impl
