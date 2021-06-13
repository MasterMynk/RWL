#pragma once
#include "rwl/Color.hpp"
#include "rwl/Log.hpp"
#include "rwl/Vec2.hpp"
#include <xcb/xcb.h>

namespace rwl {
  class Window;

  namespace impl {
    template <typename T>
    class RectPtrComm;

    template <typename T>
    class RectPtrComm;

    class WinComm {
    protected:
#if RWL_PLATFORM == LINUX
      xcb_window_t m_win;
      Pos m_pos;
      Dim m_dim;
      Color m_bgColor;
#endif
    public:
      /***************************** Constructors *****************************/
      WinComm(const xcb_window_t &winId, const Pos &pos, const Dim &dim,
              const Color &bgColor);

      /****************************** Operators ******************************/
      /****************************** Operator= ******************************/
      WinComm &operator=(const WinComm &other);

      inline WinComm &operator=(const Pos &other) {
        return this->setPos(other);
      }
      inline WinComm &operator=(const Dim &other) {
        return this->setDim(other);
      }
      inline WinComm &operator=(const Color &bgColor) {
        return this->setBgColor(bgColor);
      }

      /****************************** Operator== ******************************/
      inline bool operator==(const Pos &other) { return this->m_pos == other; }
      inline bool operator==(const Dim &other) { return this->m_dim == other; }
      inline bool operator==(const Color &other) {
        return this->m_bgColor == other;
      }

      inline bool operator==(const WinComm &other) {
        return (*this == other.m_pos && *this == other.m_dim &&
                *this == other.m_bgColor);
      }

      /****************************** Functions ******************************/
      WinComm &show();
      WinComm &showNoUpdate();

      WinComm &hide();
      WinComm &hideNoUpdate();

      /******************************* Getters *******************************/
      inline const Pos &getPos() const {
        impl::log<impl::LogLevel::NoImp>("Returning Window Position as ",
                                         m_pos);
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

      /******************************* Setters *******************************/
      inline WinComm &setPos(const Pos &other) {
        this->m_pos = other;
        impl::log<impl::LogLevel::NoImp>("Set Window Position to ",
                                         this->m_pos);
        return *this;
      }
      inline WinComm &setDim(const Dim &other) {
        this->m_dim = other;
        impl::log<impl::LogLevel::NoImp>("Set Window Dimensions to ",
                                         this->m_dim);
        return *this;
      }
      inline WinComm &setBgColor(const Color &bgColor) {
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

      virtual ~WinComm() {}

      template <typename T>
      friend class impl::RectPtrComm;

      template <typename T>
      friend class impl::RectRefComm;

      friend ::rwl::Window;
    };

  } // namespace impl
} // namespace rwl
