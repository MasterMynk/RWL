#pragma once
#include "rwl/Drawables/DrawableBase.hpp"
#include "rwl/Log.hpp"
#include "rwl/Pen.hpp"
#include "rwl/Window.hpp"

#include <memory>
#include <xcb/xcb.h>

namespace rwl {
  template <typename T> // Only works if 3 types of args are supplied
  class Drawable;

  /*
   * This is instantiated if an lvalue reference/exisiting Pen is supplied.
   * This class stores a reference to the existing variable therefore any
   * changes to that Pen are also reflected here.
   */
  template <>
  class Drawable<Pen &>: public impl::DrawableBase {
  private:
    Pen &m_pen;

  public:
    Drawable(Pen &pen) : m_pen(pen) {
      impl::log("Created Drawable with lvalue.");
    }

    Pen &pen() const {
      impl::log<impl::LogLevel::NoImp>("Returning Pen");
      return m_pen;
    }
  };

  /*
   * This is for when a rvalue reference/temporary Pen is supplied. As you can't
   * store a reference to it, a copy is stored.
   */
  template <>
  class Drawable<Pen &&>: public impl::DrawableBase {
  private:
    Pen m_pen;

  public:
    Drawable(Pen &&pen) : m_pen(std::move(pen)) {
      impl::log("Created Drawable with rvalue.");
    }

    Pen &pen() {
      impl::log<impl::LogLevel::NoImp>("Returning Pen");
      return m_pen;
    }
  };

  /*
   * When the lifetime of you existing pen is shorter you can use this method.
   * It stores the Pen on the heap with a std::shared_ptr to it. This does come
   * with some runtime cost of course.
   */
  template <>
  class Drawable<std::shared_ptr<Pen>>: public impl::DrawableBase {
  private:
    std::shared_ptr<Pen> m_pen;

  public:
    Drawable(std::shared_ptr<Pen> pen) : m_pen(pen) {
      impl::log("Created Drawable with std::shared_ptr");
    }

    Pen &pen() const {
      impl::log<impl::LogLevel::NoImp>("Returning Pen");
      return *m_pen;
    }
  };

  Drawable(Pen &)->Drawable<Pen &>;
  Drawable(Pen &&)->Drawable<Pen &&>;
  Drawable(std::shared_ptr<Pen>)->Drawable<std::shared_ptr<Pen>>;
} // namespace rwl
