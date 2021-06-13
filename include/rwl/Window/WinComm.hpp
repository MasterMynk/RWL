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
      /***************************** Operator= *****************************/
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

      /***************************** Operator== *****************************/
      inline bool operator==(const Pos &other) { return this->m_pos == other; }
      inline bool operator==(const Dim &other) { return this->m_dim == other; }
      inline bool operator==(const Color &other) {
        return this->m_bgColor == other;
      }

      inline bool operator==(const WinComm &other) {
        return (*this == other.m_pos && *this == other.m_dim &&
                *this == other.m_bgColor);
      }

      /************************* Compound Operators *************************/
      /**************************** Operator+= ****************************/
      inline WinComm &operator+=(const Pos &other) {
        this->setPos(this->m_pos + other);
        return *this;
      }
      inline WinComm &operator+=(const Dim &other) {
        this->setDim(this->m_dim + other);
        return *this;
      }

      /**************************** Operator-= ****************************/
      inline WinComm &operator-=(const Pos &other) {
        this->setPos(this->m_pos - other);
        return *this;
      }
      inline WinComm &operator-=(const Dim &other) {
        this->setDim(this->m_dim - other);
        return *this;
      }

      /**************************** Operator*= ****************************/
      inline WinComm &operator*=(const Pos &other) {
        this->setPos(this->m_pos * other);
        return *this;
      }
      inline WinComm &operator*=(const Dim &other) {
        this->setDim(this->m_dim * other);
        return *this;
      }

      /**************************** Operator/= ****************************/
      inline WinComm &operator/=(const Pos &other) {
        this->setPos(this->m_pos / other);
        return *this;
      }
      inline WinComm &operator/=(const Dim &other) {
        this->setDim(this->m_dim / other);
        return *this;
      }

      /**************************** Operator%= ****************************/
      inline WinComm &operator%=(const Pos &other) {
        this->setPos(this->m_pos % other);
        return *this;
      }
      inline WinComm &operator%=(const Dim &other) {
        this->setDim(this->m_dim % other);
        return *this;
      }

      /****************************** Functions ******************************/
      WinComm &show();
      WinComm &showNoUpdate();

      WinComm &hide();
      WinComm &hideNoUpdate();

      /******************************* Getters *******************************/
      inline const Pos &getPos() const { return m_pos; }
      inline const int16_t &getX() const { return m_pos.x; }
      inline const int16_t &getY() const { return m_pos.y; }

      inline const Dim &getDim() const { return m_dim; }
      inline const uint16_t &getWidth() const { return m_dim.width; }
      inline const uint16_t &getHeight() const { return m_dim.height; }

      inline const Color &getBgColor() const { return this->m_bgColor; }

      /******************************* Setters *******************************/
      inline WinComm &setPos(const Pos &other) {
        this->m_pos = other;
        impl::log<impl::LogLevel::NoImp>("Set Window Position to ",
                                         this->m_pos);
        return *this;
      }
      inline WinComm &setX(const int16_t &x) {
        return this->setPos({x, this->m_pos.y});
      }
      inline WinComm &setY(const int16_t &y) {
        return this->setPos({this->m_pos.x, y});
      }

      inline WinComm &setDim(const Dim &other) {
        this->m_dim = other;
        impl::log<impl::LogLevel::NoImp>("Set Window Dimensions to ",
                                         this->m_dim);
        return *this;
      }
      inline WinComm &setWidth(const uint16_t &width) {
        return this->setDim({width, this->m_dim.height});
      }
      inline WinComm &setHeight(const uint16_t &height) {
        return this->setDim({this->m_dim.height, height});
      }

      inline WinComm &setBgColor(const Color &bgColor) {
        this->m_bgColor = bgColor;
        impl::log<impl::LogLevel::NoImp>("Set Bg Color to ",
                                         this->m_bgColor.colorToStr());
        return *this;
      }

#if RWL_DEBUG == 1
      inline const xcb_window_t &getW() const { return m_win; }
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
