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
    // IsPen is declared in Drawable.hpp
    RectComm &operator=(IsPen auto &&newPen) {
      // decltype is needed otherwise type deduction fails
      Drawable<PenType>::operator=(std::forward<decltype(newPen)>(newPen));
      return *this;
    }

    RectComm &operator=(const Pos &newPos) {
      this->m_rect.x = newPos.x;
      this->m_rect.y = newPos.y;
      return *this;
    }

    RectComm &operator=(const Dim &newDim) {
      this->m_rect.width = newDim.width;
      this->m_rect.height = newDim.height;
      return *this;
    }

    /******************************** Getters ********************************/
    inline const PosRef getPos() const {
      return PosRef(this->m_rect.x, this->m_rect.y);
    }
    inline const DimRef getDim() const {
      return DimRef(this->m_rect.width, this->m_rect.height);
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
