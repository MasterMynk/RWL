#pragma once
#include "rwl/Drawables/Rect/RectPtrComm.hpp"
#include "rwl/Drawables/Rect/RectRefComm.hpp"
#include "rwl/Pen.hpp"
#include "rwl/Vec2.hpp"

#include <memory>
#include <utility>

namespace rwl {
  template <typename PenType>
  class Rect;

  // If an existing Pen is passed in use this 1
  template <>
  class Rect<Pen &>: public impl::RectRefComm<Pen &> {
  public:
    using impl::RectRefComm<Pen &>::operator=;

    Rect(Pen &pen, const Pos &pos = {0, 0}, const Dim &dim = {10, 10})
        : impl::RectRefComm<Pen &>(pen, pos, dim) {}
  };

  // If a temporary Pen is passed in use this 1
  template <>
  class Rect<Pen &&>: public impl::RectRefComm<Pen &&> {
  public:
    using impl::RectRefComm<Pen &&>::operator=;

    Rect(Pen &&pen = Pen(), const Pos &pos = {0, 0}, const Dim &dim = {10, 10})
        : impl::RectRefComm<Pen &&>(std::move(pen), pos, dim) {}
  };

  // If a shared ptr to an existing pen is passed in use this 1
  template <>
  class Rect<std::shared_ptr<Pen>>
      : public impl::RectPtrComm<std::shared_ptr<Pen>> {
  public:
    using impl::RectPtrComm<std::shared_ptr<Pen>>::operator=;

    Rect(std::shared_ptr<Pen> pen, const Pos &pos = {0, 0},
         const Dim &dim = {10, 10})
        : impl::RectPtrComm<std::shared_ptr<Pen>>(pen, pos, dim) {}
  };

  template <>
  class Rect<std::unique_ptr<Pen>>
      : public impl::RectPtrComm<std::unique_ptr<Pen>> {
  public:
    using impl::RectPtrComm<std::unique_ptr<Pen>>::operator=;
    Rect(std::shared_ptr<Pen> &&pen, const Pos &pos = {0, 0},
         const Dim &dim = {10, 10})
        : impl::RectPtrComm<std::unique_ptr<Pen>>(
              std::make_unique<Pen>(std::move(*pen)), pos, dim) {}

    Rect(std::unique_ptr<Pen> &&pen, const Pos &pos = {0, 0},
         const Dim &dim = {10, 10})
        : impl::RectPtrComm<std::unique_ptr<Pen>>(std::move(pen), pos, dim) {}
  };

  // Deduction guidelines
  Rect(Pen &, ...)->Rect<Pen &>;
  Rect(Pen &&, ...)->Rect<Pen &&>;

  Rect(std::shared_ptr<Pen>, ...)->Rect<std::shared_ptr<Pen>>;

  Rect(std::shared_ptr<Pen> &&, ...)->Rect<std::unique_ptr<Pen>>;
  Rect(std::unique_ptr<Pen> &&, ...)->Rect<std::unique_ptr<Pen>>;
} // namespace rwl
