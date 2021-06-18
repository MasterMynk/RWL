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
#include <xcb/xcb.h>

namespace rwl {
  template <typename Arr>
  concept ItArr = requires(const Arr &arr) {
    arr.begin();
    arr.end();
    { arr.size() } -> std::same_as<size_t>;
  };

  template <size_t Size = 0>
  class Rect: public impl::RectBase<Size> {
  public:
    using value_type = impl::RectBase<Size>::value_type;
    using iterator = value_type::iterator;
    using const_iterator = value_type::const_iterator;
    using reverse_iterator = value_type::reverse_iterator;
    using const_reverse_iterator = value_type::const_reverse_iterator;

  private:
    value_type m_rects;

  private:
    /******************************** Helpers ********************************/
    Rect &eqImpl(ItArr auto &&rects) {
      if constexpr (std::is_same_v<std::vector<PosDim>, value_type>)
        this->m_rects = std::move(rects);
      else
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
    /********************************* Ctors *********************************/
    // If m_rects is a vector, then only this ctor is enabled
    Rect(const size_t &length) requires
        std::is_same_v<std::vector<PosDim>, value_type>: m_rects(length) {}
    Rect(const Rect &other) : m_rects(other.m_rects) {}
    Rect(const PosDim &rect = PosDim()) : m_rects{rect} {}
    Rect(Rect &&other) : m_rects(std::move(other.m_rects)) {}
    Rect(const std::initializer_list<PosDim> &rects) { *this = rects; }

    template <size_t OSize>
    Rect(const std::array<PosDim, OSize> &rects) : m_rects(rects) {}

    /******************************* Functions *******************************/
    void draw(Window &win, const Pen &pen = Pen()) override {
      xcb_poly_rectangle(impl::core::conn, win.m_win, pen.m_pen, this->size(),
                         reinterpret_cast<xcb_rectangle_t *>(m_rects.data()));
    }

    /******************************* Iterators *******************************/
    inline iterator begin() { return this->m_rects.begin(); }
    inline reverse_iterator rbegin() { return this->m_rects.rbegin(); }
    inline const const_iterator cbegin() const { return m_rects.cbegin(); }
    inline const const_iterator begin() const { return this->m_rects.cbegin(); }
    inline const const_iterator rbegin() const {
      return this->m_rects.crbegin();
    }
    inline const const_reverse_iterator crbegin() {
      return this->m_rects.crbegin();
    }

    inline iterator end() { return this->m_rects.end(); }
    inline reverse_iterator rend() { return this->m_rects.rend(); }
    inline const const_iterator cend() const { return m_rects.cend(); }
    inline const const_iterator end() const { return this->m_rects.cend(); }
    inline const const_iterator rend() const { return this->m_rects.crend(); }
    inline const const_reverse_iterator crend() {
      return this->m_rects.crend();
    }

    /******************************* Operators *******************************/
    /********************************** [] **********************************/
    PosDim &operator[](const size_t &ind) { return this->m_rects[ind]; }

    const PosDim &operator[](const size_t &ind) const {
      return this->m_rects[ind];
    }

    /********************************** = **********************************/
    Rect &operator=(const PosDim &rect) { // When a single value is provided
      // Assign it to everything
      this->m_rects.fill(rect);
      return *this;
    }

    inline Rect &operator=(const ItArr auto &rects) {
      return this->eqImpl(rects);
    }

    inline Rect &operator=(const Rect<Size> &other) { // Copy assignment
      return this->eqImpl(other);
    }

    inline Rect &operator=(Rect<Size> &&other) {
      return this->eqImpl(std::move(other));
    }

    Rect &operator=(std::vector<PosDim> &&rects) {
      if constexpr (std::is_same_v<std::vector<PosDim>, value_type>)
        this->m_rects = std::move(rects);
      else
        return this->eqImpl(rects);

      return *this;
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

    /******************************** Getters ********************************/
    constexpr inline size_t size() const { return this->m_rects.size(); }
    inline PosDim *&data() { return this->m_rects.data(); }
    inline value_type &arr() { return this->m_rects; }

    /******************************** Friends ********************************/
    template <size_t OSize>
    friend class Rect;
  };
} // namespace rwl
