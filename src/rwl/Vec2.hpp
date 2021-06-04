#pragma once
#include <cmath>
#include <iostream>

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
    Vec2<Any> &operator=(const Any &xAndY) {
      x = xAndY;
      y = xAndY;

      return *this;
    }

    Vec2<Any> operator+(const Vec2<Any> &other) {
      return Vec2<Any>(this->x + other.x, this->y + other.y);
    }
    Vec2<Any> operator+(const Any &toAdd) {
      return Vec2<Any>(this->x + toAdd, this->y + toAdd);
    }

    Vec2<Any> operator-(const Vec2<Any> &other) {
      return Vec2<Any>(this->x - other.x, this->y - other.y);
    }
    Vec2<Any> operator-(const Any &toSub) {
      return Vec2<Any>(this->x - toSub, this->y - toSub);
    }

    Vec2<Any> operator*(const Vec2<Any> &other) {
      return Vec2<Any>(this->x * other.x, this->y * other.y);
    }
    Vec2<Any> operator*(const Any &toMul) {
      return Vec2<Any>(this->x * toMul, this->y * toMul);
    }

    Vec2<Any> operator/(const Vec2<Any> &other) {
      return Vec2<Any>(this->x / other.x, this->y / other.y);
    }
    Vec2<Any> operator/(const Any &toDiv) {
      return Vec2<Any>(this->x / toDiv, this->y / toDiv);
    }

    Vec2<Any> operator%(const Vec2<Any> &other) {
      if constexpr (std::is_floating_point_v<Any>)
        return Vec2<Any>(fmod(this->x, other.x), fmod(this->y, other.y));
      else
        return Vec2<Any>(this->x % other.x, this->y % other.y);
    }
    Vec2<Any> operator%(const Any &toMod) {
      if constexpr (std::is_floating_point_v<Any>)
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
