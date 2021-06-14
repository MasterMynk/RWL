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
    PosDim(const Pos &p_pos = {0, 0}, const Dim &p_dim = {10, 10});

    /******************************* Operators *******************************/
    /****************************** Operator= ******************************/
    inline PosDim &operator=(const Pos &pos) {
      this->pos = pos;
      return *this;
    }
    inline PosDim &operator=(const Dim &dim) {
      this->dim = dim;
      return *this;
    }
    PosDim &operator=(const PosDim &other);

    /********************* Normal Arithmatic Operators *********************/
    /***************************** Operator+ *****************************/
    inline PosDim operator+(const Pos &pos) {
      return PosDim(this->pos + pos, this->dim);
    }
    inline PosDim operator+(const Dim &dim) {
      return PosDim(this->pos, this->dim + dim);
    }
    inline PosDim operator+(const PosDim &other) {
      return PosDim(this->pos + other.dim, this->dim + other.dim);
    }

    /***************************** Operator- *****************************/
    inline PosDim operator-(const Pos &pos) {
      return PosDim(this->pos - pos, this->dim);
    }
    inline PosDim operator-(const Dim &dim) {
      return PosDim(this->pos, this->dim - dim);
    }
    inline PosDim operator-(const PosDim &other) {
      return PosDim(this->pos - other.dim, this->dim - other.dim);
    }

    /***************************** Operator* *****************************/
    inline PosDim operator*(const Pos &pos) {
      return PosDim(this->pos * pos, this->dim);
    }
    inline PosDim operator*(const Dim &dim) {
      return PosDim(this->pos, this->dim * dim);
    }
    inline PosDim operator*(const PosDim &other) {
      return PosDim(this->pos * other.dim, this->dim * other.dim);
    }

    /***************************** Operator/ *****************************/
    inline PosDim operator/(const Pos &pos) {
      return PosDim(this->pos / pos, this->dim);
    }
    inline PosDim operator/(const Dim &dim) {
      return PosDim(this->pos, this->dim / dim);
    }
    inline PosDim operator/(const PosDim &other) {
      return PosDim(this->pos / other.dim, this->dim / other.dim);
    }

    /***************************** Operator% *****************************/
    inline PosDim operator%(const Pos &pos) {
      return PosDim(this->pos % pos, this->dim);
    }
    inline PosDim operator%(const Dim &dim) {
      return PosDim(this->pos, this->dim % dim);
    }
    inline PosDim operator%(const PosDim &other) {
      return PosDim(this->pos % other.dim, this->dim % other.dim);
    }

    /************************** Compound Operators **************************/
    /***************************** Operator+= *****************************/
    inline PosDim &operator+=(const Pos &pos) {
      this->pos += pos;
      return *this;
    }
    inline PosDim &operator+=(const Dim &dim) {
      this->dim += dim;
      return *this;
    }
    PosDim &operator+=(const PosDim &other);

    /***************************** Operator-= *****************************/
    inline PosDim &operator-=(const Pos &pos) {
      this->pos -= pos;
      return *this;
    }
    inline PosDim &operator-=(const Dim &dim) {
      this->dim -= dim;
      return *this;
    }
    PosDim &operator-=(const PosDim &other);

    /***************************** Operator*= *****************************/
    inline PosDim &operator*=(const Pos &pos) {
      this->pos *= pos;
      return *this;
    }
    inline PosDim &operator*=(const Dim &dim) {
      this->dim *= dim;
      return *this;
    }
    PosDim &operator*=(const PosDim &other);

    /***************************** Operator/= *****************************/
    inline PosDim &operator/=(const Pos &pos) {
      this->pos /= pos;
      return *this;
    }
    inline PosDim &operator/=(const Dim &dim) {
      this->dim /= dim;
      return *this;
    }
    PosDim &operator/=(const PosDim &other);

    /***************************** Operator%= *****************************/
    inline PosDim &operator%=(const Pos &pos) {
      this->pos %= pos;
      return *this;
    }
    inline PosDim &operator%=(const Dim &dim) {
      this->dim %= dim;
      return *this;
    }
    PosDim &operator%=(const PosDim &other);
  };

  inline std::ostream &operator<<(std::ostream &cout, const PosDim &toPrint) {
    return (cout << toPrint.pos << "\n" << toPrint.dim);
  }
} // namespace rwl
