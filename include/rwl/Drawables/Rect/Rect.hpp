#pragma once
#include "rwl/Drawables/Drawable.hpp"
#include "rwl/Drawables/Rect/RectBase.hpp"
#include "rwl/Pen.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"

#include <algorithm>
#include <array>
#include <concepts>
#include <initializer_list>
#include <type_traits>
#include <xcb/xcb.h>

namespace rwl {
  template <size_t Size = 0>
  class Rect: public impl::RectBase<Size> {
  private:
    using parentClass = impl::RectBase<Size>;
    template <size_t OSize>
    using valueTypeNoSize = typename parentClass::valueTypeNoSize<OSize>;

  public:
    using value_type = typename parentClass::value_type;

  public:
    using parentClass::RectBase; // Ctors from base class

  private:
    /******************************* Helpers *******************************/
    inline Rect &eqImpl(ItArr auto &&rects) {
      std::copy_n(rects.begin(), std::min(this->size(), rects.size()),
                  this->begin());
      return *this;
    }

    inline Rect &plusEqImpl(const ItArr auto &rects) {
      std::transform(
          rects.begin(),
          rects.end() -
              (rects.size() > this->size() ? (rects.size() - this->size()) : 0),
          this->begin(), this->begin(),
          [](const PosDim &fir, const PosDim &sec) { return sec + fir; });

      return *this;
    }

    inline Rect &minEqImpl(const ItArr auto &rects) {
      std::transform(
          rects.begin(),
          rects.end() -
              (rects.size() > this->size() ? (rects.size() - this->size()) : 0),
          this->begin(), this->begin(),
          [](const PosDim &fir, const PosDim &sec) { return sec - fir; });

      return *this;
    }

    inline Rect &mulEqImpl(const ItArr auto &rects) {
      std::transform(
          rects.begin(),
          rects.end() -
              (rects.size() > this->size() ? (rects.size() - this->size()) : 0),
          this->begin(), this->begin(),
          [](const PosDim &fir, const PosDim &sec) { return sec * fir; });

      return *this;
    }

    inline Rect &divEqImpl(const ItArr auto &rects) {
      std::transform(
          rects.begin(),
          rects.end() -
              (rects.size() > this->size() ? (rects.size() - this->size()) : 0),
          this->begin(), this->begin(),
          [](const PosDim &fir, const PosDim &sec) { return sec / fir; });

      return *this;
    }

    inline Rect &modEqImpl(const ItArr auto &rects) {
      std::transform(
          rects.begin(),
          rects.end() -
              (rects.size() > this->size() ? (rects.size() - this->size()) : 0),
          this->begin(), this->begin(),
          [](const PosDim &fir, const PosDim &sec) { return sec % fir; });

      return *this;
    }

  public:
    /****************************** Functions ******************************/
    inline void draw(Window &win, const Pen &pen = Pen()) override {
      xcb_poly_rectangle(impl::core::conn, win.m_win, pen.m_pen, this->size(),
                         reinterpret_cast<xcb_rectangle_t *>(this->data()));
    }

    /********************************** = **********************************/
    inline Rect &operator=(const PosDim &rect) {
      parentClass::operator=(rect);
      return *this;
    }

    inline Rect &operator=(const ItArr auto &rects) {
      return this->eqImpl(rects);
    }

    inline Rect &operator=(const Rect<Size> &other) { // Copy assignment
      return this->eqImpl(other);
    }

    inline Rect &operator=(const std::initializer_list<PosDim> &rects) {
      return this->eqImpl(rects);
    }

    /*********************************** + ***********************************/
    inline Rect operator+(const PosDim &rect) const {
      return Rect(*this) += rect;
    }
    inline Rect operator+(const ItArr auto &rects) const {
      return Rect(*this) += rects;
    }
    inline Rect operator+(const std::initializer_list<PosDim> &rects) const {
      return Rect(*this) += rects;
    }

    /*********************************** - ***********************************/
    inline Rect operator-(const PosDim &rect) const {
      return Rect(*this) -= rect;
    }
    inline Rect operator-(const ItArr auto &rects) const {
      return Rect(*this) -= rects;
    }
    inline Rect operator-(const std::initializer_list<PosDim> &rects) const {
      return Rect(*this) -= rects;
    }

    /*********************************** * ***********************************/
    inline Rect operator*(const PosDim &rect) const {
      return Rect(*this) *= rect;
    }
    inline Rect operator*(const ItArr auto &rects) const {
      return Rect(*this) *= rects;
    }
    inline Rect operator*(const std::initializer_list<PosDim> &rects) const {
      return Rect(*this) *= rects;
    }

    /*********************************** / ***********************************/
    inline Rect operator/(const PosDim &rect) const {
      return Rect(*this) /= rect;
    }
    inline Rect operator/(const ItArr auto &rects) const {
      return Rect(*this) /= rects;
    }
    inline Rect operator/(const std::initializer_list<PosDim> &rects) const {
      return Rect(*this) /= rects;
    }

    /*********************************** % ***********************************/
    inline Rect operator%(const PosDim &rect) const {
      return Rect(*this) %= rect;
    }
    inline Rect operator%(const ItArr auto &rects) const {
      return Rect(*this) %= rects;
    }
    inline Rect operator%(const std::initializer_list<PosDim> &rects) const {
      return Rect(*this) %= rects;
    }

    /********************************** += **********************************/
    Rect &operator+=(const PosDim &rect) {
      for (auto &i : this->m_rects)
        i += rect;

      return *this;
    }

    inline Rect &operator+=(const ItArr auto &rects) {
      return this->plusEqImpl(rects);
    }
    inline Rect &operator+=(const std::initializer_list<PosDim> &rects) {
      return this->plusEqImpl(rects);
    }

    /********************************** -= **********************************/
    Rect &operator-=(const PosDim &rect) {
      for (auto &i : this->m_rects)
        i -= rect;

      return *this;
    }

    inline Rect &operator-=(const ItArr auto &rects) {
      return this->minEqImpl(rects);
    }

    inline Rect &operator-=(const std::initializer_list<PosDim> &rects) {
      return this->minEqImpl(rects);
    }

    /********************************** *= **********************************/
    Rect &operator*=(const PosDim &rect) {
      for (auto &i : this->m_rects)
        i *= rect;

      return *this;
    }

    inline Rect &operator*=(const ItArr auto &rects) {
      return this->mulEqImpl(rects);
    }

    inline Rect &operator*=(const std::initializer_list<PosDim> &rects) {
      return this->mulEqImpl(rects);
    }

    /********************************** /= **********************************/
    Rect &operator/=(const PosDim &rect) {
      for (auto &i : this->m_rects)
        i /= rect;

      return *this;
    }

    inline Rect &operator/=(const ItArr auto &rects) {
      return this->divEqImpl(rects);
    }

    inline Rect &operator/=(const std::initializer_list<PosDim> &rects) {
      return this->divEqImpl(rects);
    }

    /********************************** %= **********************************/
    Rect &operator%=(const PosDim &rect) {
      for (auto &i : this->m_rects)
        i %= rect;

      return *this;
    }

    inline Rect &operator%=(const ItArr auto &rects) {
      return this->modEqImpl(rects);
    }

    inline Rect &operator%=(const std::initializer_list<PosDim> &rects) {
      return this->modEqImpl(rects);
    }

    /******************************** Friends ********************************/
    template <size_t OSize>
    friend class Rect;
  };

  Rect(size_t)->Rect<0>;
} // namespace rwl
