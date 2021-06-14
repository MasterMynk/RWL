#include "rwl/PosDim.hpp"

namespace rwl {
  PosDim::PosDim(const Pos &p_pos, const Dim &p_dim) : pos(p_pos), dim(p_dim) {}

  PosDim &PosDim::operator=(const PosDim &other) {
    this->pos = other.pos;
    this->dim = other.dim;

    return *this;
  }

  PosDim &PosDim::operator+=(const PosDim &other) {
    this->pos += other.pos;
    this->dim += other.dim;

    return *this;
  }

  PosDim &PosDim::operator-=(const PosDim &other) {
    this->pos -= other.pos;
    this->dim -= other.dim;

    return *this;
  }

  PosDim &PosDim::operator*=(const PosDim &other) {
    this->pos *= other.pos;
    this->dim *= other.dim;

    return *this;
  }

  PosDim &PosDim::operator/=(const PosDim &other) {
    this->pos /= other.pos;
    this->dim /= other.dim;

    return *this;
  }

  PosDim &PosDim::operator%=(const PosDim &other) {
    this->pos %= other.pos;
    this->dim %= other.dim;

    return *this;
  }
} // namespace rwl
