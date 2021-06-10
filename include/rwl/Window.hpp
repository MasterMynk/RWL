#pragma once
#include "rwl/Color.hpp"
#include "rwl/Log.hpp"
#include "rwl/Vec2.hpp"
#include <xcb/xcb.h>

namespace rwl {
  namespace impl {
    template <typename T>
    class RectPtrComm;

    template <typename T>
    class RectPtrComm;
  } // namespace impl

  class Window {
  private:
#if RWL_PLATFORM == LINUX
    xcb_window_t m_win;
    Pos m_pos;
    Dim m_dim;
    Color m_bgColor;
#endif
  public:
    explicit Window(Window &&other);
    explicit Window(const Window &other);
    Window(const Pos &pos = {0, 0}, const Dim &dim = {640, 480},
           const Color &bgColor = Color::White);

    Window &operator=(const Window &other);

    Window &show();
    Window &showNoUpdate();

    Window &hide();
    Window &hideNoUpdate();

    inline const Pos &getPos() const {
      impl::log<impl::LogLevel::NoImp>("Returning Window Position as ", m_pos);
      return m_pos;
    }
    inline const Dim &getDim() const {
      impl::log<impl::LogLevel::NoImp>("Returning Window Dimensions as ",
                                       m_dim);
      return m_dim;
    }
    inline const Color &getBgColor() const {
      impl::log<impl::LogLevel::NoImp>("Returning Bg Color as ",
                                       this->m_bgColor.colorToStr());
      return this->m_bgColor;
    }

    inline Window &setPos(const Pos &other) {
      this->m_pos = other;
      impl::log<impl::LogLevel::NoImp>("Set Window Position to ", this->m_pos);
      return *this;
    }
    inline Window &setDim(const Dim &other) {
      this->m_dim = other;
      impl::log<impl::LogLevel::NoImp>("Set Window Dimensions to ",
                                       this->m_dim);
      return *this;
    }
    inline const Window &setBgColor(const Color &bgColor) {
      this->m_bgColor = bgColor;
      impl::log<impl::LogLevel::NoImp>("Set Bg Color to ",
                                       this->m_bgColor.colorToStr());
      return *this;
    }

#if RWL_DEBUG == 1
    inline const xcb_window_t &getW() const {
      impl::log<impl::LogLevel::NoImp>("Returning Window id.");
      return m_win;
    }
#endif

    ~Window();

    template <typename T>
    friend class impl::RectPtrComm;

    template <typename T>
    friend class impl::RectRefComm;
  };
} // namespace rwl
