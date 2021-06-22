#pragma once
#include "rwl/Log.hpp"
#include "rwl/Vec2.hpp"

#include <iostream>

namespace rwl {
  struct PosDim {
  public:
    Pos pos;
    Dim dim;

  public:
    PosDim(const Pos &p_pos = {0, 0}, const Dim &p_dim = {0, 0});

    /******************************* Functions *******************************/
    inline PosDim addSelf() const { return *this + *this; }
    inline PosDim subSelf() const { return *this - *this; }
    inline PosDim mulSelf() const { return *this * *this; }
    inline PosDim divSelf() const { return *this / *this; }
    inline PosDim modSelf() const { return *this % *this; }

    /*********************************** = ***********************************/
    inline PosDim &operator=(const Pos &pos) {
      this->pos = pos;
      return *this;
    }
    inline PosDim &operator=(const Dim &dim) {
      this->dim = dim;
      return *this;
    }
    PosDim &operator=(const PosDim &other);

    /*********************************** + ***********************************/
    inline PosDim operator+(const Pos &pos) const {
      return PosDim(this->pos + pos, this->dim);
    }
    inline PosDim operator+(const Dim &dim) const {
      return PosDim(this->pos, this->dim + dim);
    }
    inline PosDim operator+(const PosDim &other) const {
      return PosDim(this->pos + other.pos, this->dim + other.dim);
    }

    /*********************************** - ***********************************/
    inline PosDim operator-(const Pos &pos) const {
      return PosDim(this->pos - pos, this->dim);
    }
    inline PosDim operator-(const Dim &dim) const {
      return PosDim(this->pos, this->dim - dim);
    }
    inline PosDim operator-(const PosDim &other) const {
      return PosDim(this->pos - other.pos, this->dim - other.dim);
    }

    /*********************************** * ***********************************/
    inline PosDim operator*(const Pos &pos) const {
      return PosDim(this->pos * pos, this->dim);
    }
    inline PosDim operator*(const Dim &dim) const {
      return PosDim(this->pos, this->dim * dim);
    }
    inline PosDim operator*(const PosDim &other) const {
      return PosDim(this->pos * other.pos, this->dim * other.dim);
    }

    /*********************************** / ***********************************/
    inline PosDim operator/(const Pos &pos) const {
      return PosDim(this->pos / pos, this->dim);
    }
    inline PosDim operator/(const Dim &dim) const {
      return PosDim(this->pos, this->dim / dim);
    }
    inline PosDim operator/(const PosDim &other) const {
      return PosDim(this->pos / other.pos, this->dim / other.dim);
    }

    /*********************************** % ***********************************/
    inline PosDim operator%(const Pos &pos) const {
      return PosDim(this->pos % pos, this->dim);
    }
    inline PosDim operator%(const Dim &dim) const {
      return PosDim(this->pos, this->dim % dim);
    }
    inline PosDim operator%(const PosDim &other) const {
      return PosDim(this->pos % other.pos, this->dim % other.dim);
    }

    /********************************** += **********************************/
    inline PosDim &operator+=(const Pos &pos) {
      this->pos += pos;
      return *this;
    }
    inline PosDim &operator+=(const Dim &dim) {
      this->dim += dim;
      return *this;
    }
    PosDim &operator+=(const PosDim &other);

    /********************************** -= **********************************/
    inline PosDim &operator-=(const Pos &pos) {
      this->pos -= pos;
      return *this;
    }
    inline PosDim &operator-=(const Dim &dim) {
      this->dim -= dim;
      return *this;
    }
    PosDim &operator-=(const PosDim &other);

    /********************************** *= **********************************/
    inline PosDim &operator*=(const Pos &pos) {
      this->pos *= pos;
      return *this;
    }
    inline PosDim &operator*=(const Dim &dim) {
      this->dim *= dim;
      return *this;
    }
    PosDim &operator*=(const PosDim &other);

    /********************************** /= **********************************/
    inline PosDim &operator/=(const Pos &pos) {
      this->pos /= pos;
      return *this;
    }
    inline PosDim &operator/=(const Dim &dim) {
      this->dim /= dim;
      return *this;
    }
    PosDim &operator/=(const PosDim &other);

    /********************************** %= **********************************/
    inline PosDim &operator%=(const Pos &pos) {
      this->pos %= pos;
      return *this;
    }
    inline PosDim &operator%=(const Dim &dim) {
      this->dim %= dim;
      return *this;
    }
    PosDim &operator%=(const PosDim &other);

    /*********************************** ++ ***********************************/
    inline PosDim operator++() { // Prefix: ++x
      ++this->pos;
      ++this->dim;
      return *this;
    }
    inline PosDim operator++(int) { // Postfix: x++
      auto other = *this;
      ++(*this);
      return other;
    }

    /*********************************** -- ***********************************/
    inline PosDim operator--() { // Prefix: --x
      --this->pos;
      --this->dim;
      return *this;
    }
    inline PosDim operator--(int) { // Postfix: x--
      auto other = *this;
      --(*this);
      return other;
    }
  };

  inline std::ostream &operator<<(std::ostream &cout, const PosDim &toPrint) {
    return (cout << "{ " << toPrint.pos << ", " << toPrint.dim << " }");
  }

} // namespace rwl
