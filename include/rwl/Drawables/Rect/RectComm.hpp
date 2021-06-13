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
  template <typename PenType>
  class RectComm: public Drawable<PenType> {
  protected:
    xcb_rectangle_t m_rect;

  protected:
    bool operator=(const xcb_rectangle_t other) {
      return (this->m_rect.x == other.x && this->m_rect.y == other.y &&
              this->m_rect.width == other.width &&
              this->m_rect.height == other.height);
    }

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
    inline void operator=(IsPen auto &&newPen) {
      Drawable<PenType>::operator=(std::forward<decltype(newPen)>(newPen));
    }

    /********************** Regular arithmatic operators **********************/
    /******************************* Operator+ *******************************/
    Pos operator+(const Pos &otherPos) {
      return Pos(this->m_rect.x + otherPos.x, this->m_rect.y + otherPos.y);
    }

    Dim operator+(const Dim &otherDim) {
      return Dim(this->m_rect.width + otherDim.width,
                 this->m_rect.height + otherDim.height);
    }

    /******************************* Operator- *******************************/
    Pos operator-(const Pos &otherPos) {
      return Pos(this->m_rect.x - otherPos.x, this->m_rect.y - otherPos.y);
    }

    Dim operator-(const Dim &otherDim) {
      return Dim(this->m_rect.width - otherDim.width,
                 this->m_rect.height - otherDim.height);
    }

    /******************************* Operator* *******************************/
    Pos operator*(const Pos &otherPos) {
      return Pos(this->m_rect.x * otherPos.x, this->m_rect.y * otherPos.y);
    }

    Dim operator*(const Dim &otherDim) {
      return Dim(this->m_rect.width * otherDim.width,
                 this->m_rect.height * otherDim.height);
    }

    /******************************* Operator/ *******************************/
    Pos operator/(const Pos &otherPos) {
      return Pos(this->m_rect.x / otherPos.x, this->m_rect.y / otherPos.y);
    }

    Dim operator/(const Dim &otherDim) {
      return Dim(this->m_rect.width / otherDim.width,
                 this->m_rect.height / otherDim.height);
    }

    /******************************* Operator% *******************************/
    Pos operator%(const Pos &otherPos) {
      return Pos(this->m_rect.x % otherPos.x, this->m_rect.y % otherPos.y);
    }

    Dim operator%(const Dim &otherDim) {
      return Dim(this->m_rect.width % otherDim.width,
                 this->m_rect.height % otherDim.height);
    }

    /*************************** Compound Operators ***************************/
    /******************************* Operator+= *******************************/
    RectComm &operator+=(const Pos &otherPos) {
      this->m_rect.x += otherPos.x;
      this->m_rect.y += otherPos.y;
      return *this;
    }

    RectComm &operator+=(const Dim &otherDim) {
      this->m_rect.width += otherDim.width;
      this->m_rect.height += otherDim.height;
      return *this;
    }

    template <typename T>
    RectComm &operator+=(const RectComm<T> &other) {
      this->m_rect.x += other.m_rect.x;
      this->m_rect.y += other.m_rect.y;
      this->m_rect.width += other.m_rect.width;
      this->m_rect.height += other.m_rect.height;
      return *this;
    }

    /******************************* Operator-= *******************************/
    RectComm &operator-=(const Pos &otherPos) {
      this->m_rect.x -= otherPos.x;
      this->m_rect.y -= otherPos.y;
      return *this;
    }

    RectComm &operator-=(const Dim &otherDim) {
      this->m_rect.width -= otherDim.width;
      this->m_rect.height -= otherDim.height;
      return *this;
    }

    template <typename T>
    RectComm &operator-=(const RectComm<T> &other) {
      this->m_rect.x -= other.m_rect.x;
      this->m_rect.y -= other.m_rect.y;
      this->m_rect.width -= other.m_rect.width;
      this->m_rect.height -= other.m_rect.height;
      return *this;
    }

    /******************************* Operator*= *******************************/
    RectComm &operator*=(const Pos &otherPos) {
      this->m_rect.x *= otherPos.x;
      this->m_rect.y *= otherPos.y;
      return *this;
    }

    RectComm &operator*=(const Dim &otherDim) {
      this->m_rect.width *= otherDim.width;
      this->m_rect.height *= otherDim.height;
      return *this;
    }

    RectComm &operator*=(const RectComm &other) {
      this->m_rect.x *= other.m_rect.x;
      this->m_rect.y *= other.m_rect.y;
      this->m_rect.width *= other.m_rect.width;
      this->m_rect.height *= other.m_rect.height;
      return *this;
    }

    /******************************* Operator/= *******************************/
    RectComm &operator/=(const Pos &otherPos) {
      this->m_rect.x /= otherPos.x;
      this->m_rect.y /= otherPos.y;
      return *this;
    }

    RectComm &operator/=(const Dim &otherDim) {
      this->m_rect.width /= otherDim.width;
      this->m_rect.height /= otherDim.height;
      return *this;
    }

    RectComm &operator/=(const RectComm &other) {
      this->m_rect.x /= other.m_rect.x;
      this->m_rect.y /= other.m_rect.y;
      this->m_rect.width /= other.m_rect.width;
      this->m_rect.height /= other.m_rect.height;
      return *this;
    }

    /******************************* Operator%= *******************************/
    RectComm &operator%=(const Pos &otherPos) {
      this->m_rect.x %= otherPos.x;
      this->m_rect.y %= otherPos.y;
      return *this;
    }

    RectComm &operator%=(const Dim &otherDim) {
      this->m_rect.width %= otherDim.width;
      this->m_rect.height %= otherDim.height;
      return *this;
    }

    RectComm &operator%=(const RectComm &other) {
      this->m_rect.x %= other.m_rect.x;
      this->m_rect.y %= other.m_rect.y;
      this->m_rect.width %= other.m_rect.width;
      this->m_rect.height %= other.m_rect.height;
      return *this;
    }

    /************************* Comparision Operators *************************/
    bool operator==(const Pos &otherPos) {
      return (this->m_rect.x == otherPos.x && this->m_rect.y == otherPos.y);
    }

    bool operator==(const Dim &otherDim) {
      return (this->m_rect.width == otherDim.width &&
              this->m_rect.height == otherDim.height);
    }

    // As the above override the base class's operator==, we have to declare it
    // again and tell it to use the Drawable's operator==.
    inline bool operator==(const Pen &otherPen) {
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

    // All template instantiations of RectComm are now friends :)
    template <typename T>
    friend class RectComm;
  };
} // namespace rwl::impl
