#pragma once
#include "rwl/Color/Color.hpp"
#include "rwl/Log.hpp"
#include <xcb/xcb.h>

namespace rwl {
  class Pen {
  private:
#if RWL_PLATFORM == LINUX
    xcb_gcontext_t m_pen;
    Color m_fgColor;
    static uint32_t s_valueMask;
#endif

  private:
    void create();
    void change();

  public:
    Pen(Pen &&other);
    Pen(const Pen &other);
    Pen(const Color &fgColor = Color::Black);

    Pen &operator=(const Pen &other);
    inline Pen &operator=(const Color &fgColor) { return setFgColor(fgColor); }

    inline const Color &getFgColor() const {
      impl::log("Returning fg color as ", this->m_fgColor.colorToStr());
      return this->m_fgColor;
    }

    Pen &setFgColor(const Color &fgColor);

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
    inline const xcb_gcontext_t getP() const {
      impl::log("Returning pen with id: ", m_pen);
      return m_pen;
    }
#endif

    ~Pen();
  };
} // namespace rwl
