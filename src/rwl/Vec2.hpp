#pragma once
#include <cmath>
#include <iostream>
#include <functional>

namespace rwl {
  template <typename Any>
  struct Vec2 {
  public:
    union {
      struct {
        Any x, y;
      };
      struct {
        Any width, height;
      };
    };

    /*********** Constructors ***********/
    Vec2(const Any &p_x, const Any &p_y) : x(p_x), y(p_y) {}
    Vec2(const Any &xAndY = Any()) : x(xAndY), y(xAndY) {}

    /********************* Operator Overloads *********************/
    Vec2 &operator=(const Any &xAndY) {
      x = xAndY;
      y = xAndY;

      return *this;
    }

    template <typename Any0,
              typename = std::enable_if_t<std::is_fundamental_v<Any0>>>
    Vec2 operator+(const Any0 &other) {
      return Vec2<Any>(this->x + other, this->y + other);
    }
    template <typename Any0>
    Vec2 operator+(const Vec2<Any0> &other) {
      return Vec2<Any>(this->x + other.x, this->y + other.y);
    }

    template <typename Any0,
              typename = std::enable_if_t<std::is_fundamental_v<Any0>>>
    Vec2 operator-(const Any0 &other) {
      return Vec2<Any>(this->x - other, this->y - other);
    }
    template <typename Any0>
    Vec2 operator-(const Vec2<Any0> &other) {
      return Vec2<Any>(this->x - other.x, this->y - other.y);
    }

    template <typename Any0,
              typename = std::enable_if_t<std::is_fundamental_v<Any0>>>
    Vec2 operator*(const Any0 &other) {
      return Vec2<Any>(this->x * other, this->y * other);
    }
    template <typename Any0>
    Vec2 operator*(const Vec2<Any0> &other) {
      return Vec2<Any>(this->x * other.x, this->y * other.y);
    }

    template <typename Any0,
              typename = std::enable_if_t<std::is_fundamental_v<Any0>>>
    Vec2 operator/(const Any0 &other) {
      return Vec2<Any>(this->x / other, this->y / other);
    }
    template <typename Any0>
    Vec2 operator/(const Vec2<Any0> &other) {
      return Vec2<Any>(this->x / other.x, this->y / other.y);
    }

    template <typename Any0>
    Vec2 operator%(const Vec2<Any0> &other) {
      if constexpr (std::is_floating_point_v<Any> ||
                    std::is_floating_point_v<Any0>)
        return Vec2<Any>(fmod(this->x, other.x), fmod(this->y, other.y));
      else
        return Vec2<Any>(this->x % other.x, this->y % other.y);
    }
    template <typename Any0>
    Vec2 operator%(const Any &toMod) {
      if constexpr (std::is_floating_point_v<Any> ||
                    std::is_floating_point_v<Any0>)
        return Vec2<Any>(fmod(this->x, toMod), fmod(this->y, toMod));
      else
        return Vec2<Any>(this->x % toMod, this->y % toMod);
    }
  };

  template <typename Any>
  std::ostream &operator<<(std::ostream &cout, Vec2<Any> toPrint) {
    return (cout << toPrint.x << ", " << toPrint.y);
  }

  typedef Vec2<int16_t> Pos;
  typedef Vec2<uint16_t> Dim;
} // namespace rwl
