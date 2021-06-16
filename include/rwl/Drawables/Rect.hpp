#pragma once
#include "rwl/Drawables/Drawable.hpp"
#include "rwl/Pen.hpp"
#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <xcb/xcb.h>

namespace rwl {
  template <size_t Size = 1>
  class Rect: public Drawable {
  public:
    using value_type = std::array<PosDim, Size>;

    using iterator = value_type::iterator;
    using const_iterator = value_type::const_iterator;
    using reverse_iterator = value_type::reverse_iterator;
    using const_reverse_iterator = value_type::const_reverse_iterator;

  private:
    value_type m_rects;

  public:
    Rect() : m_rects{} {}

    Rect(const std::initializer_list<PosDim> &rects) {
      std::copy(rects.begin(), rects.end(), m_rects.begin());
    }

    /******************************* Functions *******************************/
    void draw(Window &win, const Pen &pen = Pen()) override {
      xcb_poly_rectangle(impl::core::conn, win.m_win, pen.m_pen, Size,
                         reinterpret_cast<xcb_rectangle_t *>(m_rects.data()));
    }

    /******************************* Iterators *******************************/
    auto begin() { return this->m_rects.begin(); }
    const auto begin() const { return this->m_rects.cbegin(); }
    auto rbegin() { return this->m_rects.rbegin(); }
    auto crbegin() { return this->m_rects.crbegin(); }

    auto end() { return this->m_rects.end(); }
    const auto end() const { return this->m_rects.cend(); }
    auto rend() { return this->m_rects.rend(); }
    auto crend() { return this->m_rects.crend(); }

    /******************************* Operators *******************************/
    /********************************** [] **********************************/
    PosDim &operator[](const size_t &ind) { return this->m_rects[ind]; }

    const PosDim &operator[](const size_t &ind) const {
      return this->m_rects[ind];
    }

    /********************************** = **********************************/
    Rect &operator=(const std::array<PosDim, Size> &rects) {
      this->m_rects = rects;
      return *this;
    }
    Rect &operator=(const std::initializer_list<PosDim> &rects) {
      std::copy(rects.begin(), rects.end(), this->m_rects.begin());
      return *this;
    }

    /******************************** Getters ********************************/
    constexpr size_t size() { return Size; }
  };
} // namespace rwl
