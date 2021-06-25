#pragma once

#include "rwl/Drawables/Drawable.hpp"
#include "rwl/core.hpp"
#include <algorithm>
#include <array>
#include <utility>
#include <vector>

namespace rwl {
  template <typename Arr>
  concept ItArr = requires(const Arr &arr) { // Stands for: Iterable Array
    arr.begin();
    arr.end();
    { arr.size() } -> std::same_as<size_t>;
  };

  namespace impl {
    template <size_t Size = 0>
    class RectBase: public std::array<PosDim, Size>, public Drawable {
    protected:
      template <size_t OSize>
      using valueTypeNoSize = std::array<PosDim, OSize>;

    public:
      using value_type = valueTypeNoSize<Size>; // Snake case cos of convention

    public:
      /******************************* Ctors ********************************/
      RectBase(const RectBase &other) : value_type(other) {} // Copy
      RectBase(const PosDim &rect = PosDim()) : value_type{rect} {}
      RectBase(const std::initializer_list<PosDim> &rects) {
        std::copy_n(rects.begin(), std::min(this->size(), rects.size()),
                    this->begin());
      }

      template <size_t OSize>
      RectBase(const valueTypeNoSize<OSize> &rects) : value_type(rects) {}

      // When a single value is provided assign it to everything
      void operator=(const PosDim &rect) { this->fill(rect); }
    };

    template <>
    class RectBase<0>: public std::vector<PosDim>, public Drawable {
    protected:
      template <size_t OSize>
      using valueTypeNoSize = value_type;

    public:
      using value_type = std::vector<PosDim>; // Snake case cos of convention

    public:
      /******************************* Ctors ********************************/
      using value_type::value_type;

      // When a single value is provided assign it to everything
      void operator=(const PosDim &rect) {
        std::fill(this->begin(), this->end(), rect);
      }
    };
  } // namespace impl
} // namespace rwl
