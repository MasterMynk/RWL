#pragma once
#include "rwl/Drawables/DrawableComm.hpp"
#include "rwl/Log.hpp"
#include "rwl/Pen.hpp"
#include "rwl/Window/Window.hpp"

#include <memory>
#include <utility>
#include <xcb/xcb.h>

namespace rwl {
  // Checks if the passeed arg is Pen
  template <typename Type, typename T>
  concept IsType = std::is_same_v<Type, std::remove_cvref_t<T>>;

  template <typename T>
  concept IsPen = IsType<Pen, T>;

  template <typename PenType> // Only works if 3 types of args are supplied
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

    Pen &pen() const { return m_pen; }

    void operator=(IsPen auto &&newPen) {
      impl::log("Drawable: Changed Pen with operator=");
      this->m_pen = std::forward<decltype(newPen)>(newPen);
    }

    bool operator==(const Pen &otherPen) {
      impl::log<impl::LogLevel::NoImp>(
          "Drawable: Checking if my Pen is equal to another");
      return (this->m_pen == otherPen);
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

    Pen &pen() { return m_pen; }

    void operator=(IsPen auto &&newPen) {
      impl::log("Drawable: Changed Pen with operator=");
      this->m_pen = std::forward<decltype(newPen)>(newPen);
    }

    bool operator==(const Pen &otherPen) {
      impl::log<impl::LogLevel::NoImp>(
          "Drawable: Checking if my Pen is equal to another");
      return (this->m_pen == otherPen);
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

    Pen &pen() const { return *m_pen; }

    void operator=(IsPen auto &&newPen) {
      impl::log("Drawable: Changed Pen with operator=");
      *(this->m_pen) = std::forward<decltype(newPen)>(newPen);
    }

    bool operator==(const Pen &otherPen) {
      impl::log<impl::LogLevel::NoImp>(
          "Drawable: Checking if my Pen is equal to another");
      return (*(this->m_pen) == otherPen);
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

    Pen &pen() const { return *m_pen; }

    void operator=(IsPen auto &&newPen) {
      impl::log("Drawable: Changed Pen with operator=");
      *(this->m_pen) = std::forward<decltype(newPen)>(newPen);
    }

    bool operator==(const Pen &otherPen) {
      impl::log<impl::LogLevel::NoImp>(
          "Drawable: Checking if my Pen is equal to another");
      return (*(this->m_pen) == otherPen);
    }
  };

  Drawable(Pen &)->Drawable<Pen &>;
  Drawable(Pen &&)->Drawable<Pen &&>;
  Drawable(std::shared_ptr<Pen> &)->Drawable<std::shared_ptr<Pen>>;
  Drawable(std::unique_ptr<Pen> &&)->Drawable<std::unique_ptr<Pen>>;
} // namespace rwl
