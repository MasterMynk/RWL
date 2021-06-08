#pragma once
#include <cmath>
#include <iostream>

namespace rwl {
  template <typename T>
  concept Fundamental = std::is_fundamental_v<T>;

  template <typename T, typename T0>
  concept isFloat = std::is_floating_point_v<T> || std::is_floating_point_v<T0>;

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
    Vec2(const Any &other = Any()) : x(other), y(other) {}

  private:
    template <typename Any0>
    Vec2<Any> modImpl(const Any0 &first, const Any0 &sec) const {
      if constexpr (isFloat<Any, Any0>)
        return Vec2(fmod(this->x, first), fmod(this->y, sec));
      else
        return Vec2(this->x % first, this->y % sec);
    }

    template <typename Any0>
    Vec2 &compoundModImpl(const Any0 &first, const Any0 &sec) {
      if constexpr (isFloat<Any, Any0>) {
        this->x = fmod(this->x, first);
        this->y = fmod(this->y, sec);
      } else {
        this->x %= first;
        this->y %= sec;
      }

      return *this;
    }

  public:
    /********************* Operator Overloads *********************/
    Vec2 &operator=(const Fundamental auto &other) {
      this->x = other;
      this->y = other;

      return *this;
    }
    template <typename Any0>
    Vec2 &operator=(const Vec2<Any0> &other) {
      this->x = other.x;
      this->y = other.y;

      return *this;
    }

    inline Vec2 operator+(const Fundamental auto &other) const {
      return Vec2(this->x + other, this->y + other);
    }
    template <typename Any0>
    Vec2 operator+(const Vec2<Any0> &other) const {
      return Vec2(this->x + other.x, this->y + other.y);
    }

    inline Vec2 operator-(const Fundamental auto &other) const {
      return Vec2(this->x - other, this->y - other);
    }
    template <typename Any0>
    Vec2 operator-(const Vec2<Any0> &other) const {
      return Vec2(this->x - other.x, this->y - other.y);
    }

    inline Vec2 operator*(const Fundamental auto &other) const {
      return Vec2(this->x * other, this->y * other);
    }
    template <typename Any0>
    Vec2 operator*(const Vec2<Any0> &other) const {
      return Vec2(this->x * other.x, this->y * other.y);
    }

    inline Vec2 operator/(const Fundamental auto &other) const {
      return Vec2(this->x / other, this->y / other);
    }
    template <typename Any0>
    Vec2 operator/(const Vec2<Any0> &other) const {
      return Vec2(this->x / other.x, this->y / other.y);
    }

    inline Vec2 operator%(const Fundamental auto &other) const {
      return modImpl(other, other);
    }
    template <typename Any0>
    Vec2 operator%(const Vec2<Any0> &other) const {
      return modImpl(other.x, other.y);
    }

    Vec2 &operator+=(const Fundamental auto &other) {
      this->x += other;
      this->y += other;

      return *this;
    }
    template <typename Any0>
    Vec2 &operator+=(const Vec2<Any0> &other) {
      this->x += other.x;
      this->y += other.y;

      return *this;
    }

    Vec2 &operator-=(const Fundamental auto &other) {
      this->x -= other;
      this->y -= other;

      return *this;
    }
    template <typename Any0>
    Vec2 &operator-=(const Vec2<Any0> &other) {
      this->x -= other.x;
      this->y -= other.y;

      return *this;
    }

    Vec2 &operator*=(const Fundamental auto &other) {
      this->x *= other;
      this->y *= other;

      return *this;
    }
    template <typename Any0>
    Vec2 &operator*=(const Vec2<Any0> &other) {
      this->x *= other.x;
      this->y *= other.y;

      return *this;
    }

    Vec2 &operator/=(const Fundamental auto &other) {
      this->x /= other;
      this->y /= other;

      return *this;
    }
    template <typename Any0>
    Vec2 &operator/=(const Vec2<Any0> &other) {
      this->x /= other.x;
      this->y /= other.y;

      return *this;
    }

    inline Vec2 &operator%=(const Fundamental auto &other) {
      return compoundModImpl(other, other);
    }
    template <typename Any0>
    inline Vec2 &operator%=(const Vec2<Any0> &other) {
      return compoundModImpl(other.x, other.y);
    }

    inline bool operator==(const Fundamental auto &other) {
      return (this->x == other && this->y == other);
    }
    template <typename Any0>
    inline bool operator==(const Vec2<Any0> &other) {
      return (this->x == other.x && this->y == other.y);
    }

    template <typename Any0>
    inline bool operator!=(const Any0 &other) {
      return !(*this == other);
    }

    inline bool operator<(const Fundamental auto &other) {
      return (this->x < other || this->y < other);
    }
    template <typename Any0>
    inline bool operator<(const Vec2<Any0> &other) {
      return (this->x < other.x && this->y < other.y);
    }

    inline bool operator<=(const Fundamental auto &other) {
      return (this->x <= other || this->y <= other);
    }
    template <typename Any0>
    inline bool operator<=(const Vec2<Any0> &other) {
      return (this->x <= other.x && this->y <= other.y);
    }

    template <typename Any0>
    inline bool operator>(const Any0 &other) {
      return !(*this <= other);
    }
    template <typename Any0>
    inline bool operator>=(const Any0 &other) {
      return !(*this < other);
    }
  };

  template <typename Any>
  std::ostream &operator<<(std::ostream &cout, const Vec2<Any> &toPrint) {
    return (cout << toPrint.x << ", " << toPrint.y);
  }

  using Pos = Vec2<int16_t>;
  using Dim = Vec2<uint16_t>;
} // namespace rwl
