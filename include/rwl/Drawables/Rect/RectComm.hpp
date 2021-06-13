#pragma once

#include "rwl/Drawables/Drawable.hpp"
#include "rwl/Vec2.hpp"

#include <type_traits>
#include <utility>
#include <xcb/xcb.h>

namespace rwl::impl {
  // All code common in all Rects lives below
  template <typename PenType>
  class RectComm: public Drawable<PenType> {
  protected:
    xcb_rectangle_t m_rect;

  public:
    RectComm(PenType pen, const Pos &pos, const Dim &dim)
        : Drawable<PenType>(std::forward<std::remove_cv_t<PenType>>(pen)),
          m_rect{pos.x, pos.y, dim.width, dim.height} {}

    /******************************* Operators *******************************/
    /******************************* Operator= *******************************/
    void operator=(const Pos &newPos) {
      this->m_rect.x = newPos.x;
      this->m_rect.y = newPos.y;
    }

    void operator=(const Dim &newDim) {
      this->m_rect.width = newDim.width;
      this->m_rect.height = newDim.height;
    }

    // This just uses the overload from base class
    void operator=(IsPen auto &&newPen) {
      Drawable<PenType>::operator=(std::forward<decltype(newPen)>(newPen));
    }

    /************************* Comparision Operators *************************/
    bool operator==(const Pos &otherPos) {
      return (this->m_rect.x == otherPos.x && this->m_rect.y == otherPos.y);
    }

    bool operator==(const Dim &otherPos) {
      return (this->m_rect.width == otherPos.width &&
              this->m_rect.height == otherPos.height);
    }

    // As the above override the base class's operator==, we have to declare it
    // again and tell it to use the Drawable's operator==.
    bool operator==(const Pen &otherPen) {
      return Drawable<PenType>::operator==(otherPen);
    }

    /******************************** Getters ********************************/
    inline const Pos getPos() const {
      return Pos(this->m_rect.x, this->m_rect.y);
    }
    inline const Dim getDim() const {
      return Dim(this->m_rect.width, this->m_rect.height);
    }

    /******************************** Setters ********************************/
    RectComm &setPos(const Pos &newPos) {
      this->m_rect.x = newPos.x;
      this->m_rect.y = newPos.y;

      return *this;
    }

    RectComm &setDim(const Dim &newDim) {
      this->m_rect.width = newDim.width;
      this->m_rect.height = newDim.height;

      return *this;
    }

    virtual ~RectComm() {}
  };
} // namespace rwl::impl
