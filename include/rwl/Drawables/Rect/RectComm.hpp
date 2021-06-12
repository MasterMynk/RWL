#pragma once

#include "rwl/Drawables/Drawable.hpp"
#include "rwl/Vec2.hpp"

#include <type_traits>
#include <utility>
#include <xcb/xcb.h>

namespace rwl::impl {
  template <typename T>
  class Rect;

  // All code common in all Rects lives below
  template <typename T>
  class RectComm: public Drawable<T> {
  protected:
    xcb_rectangle_t m_rect[1];

  public:
    RectComm(T pen, const Pos &pos, const Dim &dim)
        : Drawable<T>(std::forward<std::remove_cv_t<T>>(pen)),
          m_rect{pos.x, pos.y, dim.width, dim.height} {}

    /******************************* Operators *******************************/
    RectComm &operator=(const Pen &newPen) {
      Drawable<T>::operator=(newPen);
      return *this;
    }

    inline const PosRef getPos() const {
      return PosRef(this->m_rect->x, this->m_rect->y);
    }
    inline const DimRef getDim() const {
      return DimRef(this->m_rect->width, this->m_rect->height);
    }

    RectComm &setPos(const Pos &newPos) {
      this->m_rect->x = newPos.x;
      this->m_rect->y = newPos.y;

      return *this;
    }

    RectComm &setDim(const Dim &newDim) {
      this->m_rect->width = newDim.width;
      this->m_rect->height = newDim.height;

      return *this;
    }

    virtual ~RectComm() {}
  };
} // namespace rwl::impl
