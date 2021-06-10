#pragma once
#include "rwl/Drawables/DrawableComm.hpp"
#include "rwl/Log.hpp"
#include "rwl/Pen.hpp"
#include "rwl/Window/Window.hpp"

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
  class Drawable<Pen &>: public impl::DrawableComm {
  protected:
    Pen &m_pen;

  public:
    Drawable(Pen &pen) : m_pen(pen) {}

    Pen &pen() const {
      impl::log<impl::LogLevel::NoImp>("Drawable: Returning Pen (lvalue)");
      return m_pen;
    }
  };

  /*
   * This is for when a rvalue reference/temporary Pen is supplied. As you can't
   * store a reference to it, a copy is stored.
   */
  template <>
  class Drawable<Pen &&>: public impl::DrawableComm {
  protected:
    Pen m_pen;

  public:
    Drawable(Pen &&pen) : m_pen(std::move(pen)) {}

    Pen &pen() {
      impl::log<impl::LogLevel::NoImp>("Drawable: Returning Pen (rvalue)");
      return m_pen;
    }
  };

  /*
   * When the lifetime of you existing pen is shorter you can use this method.
   * It stores the Pen on the heap with a std::shared_ptr to it. This does come
   * with some runtime cost of course.
   */
  template <>
  class Drawable<std::shared_ptr<Pen>>: public impl::DrawableComm {
  protected:
    std::shared_ptr<Pen> m_pen;

  public:
    Drawable(std::shared_ptr<Pen> pen) : m_pen(pen) {}

    Pen &pen() const {
      impl::log<impl::LogLevel::NoImp>(
          "Drawable: Returning Pen (std::shared_ptr)");
      return *m_pen;
    }
  };

  /*
   * When you want the Pen to be on the heap but you're passing in a temporary
   * ptr then this speicialization is used.
   */
  template <>
  class Drawable<std::unique_ptr<Pen>>: public impl::DrawableComm {
  protected:
    std::unique_ptr<Pen> m_pen;

  public:
    Drawable(std::unique_ptr<Pen> &&pen) : m_pen(std::move(pen)) {}

    Pen &pen() const {
      impl::log<impl::LogLevel::NoImp>(
          "Drawable: Returning Pen (std::unique_ptr)");
      return *m_pen;
    }
  };

  Drawable(Pen &)->Drawable<Pen &>;
  Drawable(Pen &&)->Drawable<Pen &&>;
  Drawable(std::shared_ptr<Pen> &)->Drawable<std::shared_ptr<Pen>>;
  Drawable(std::unique_ptr<Pen> &&)->Drawable<std::unique_ptr<Pen>>;
} // namespace rwl
