#pragma once
#include "rwl/Color/Color.hpp"
#include "rwl/Log.hpp"
#include <xcb/xcb.h>

namespace rwl {
  class Pen {
  public:
    enum class LineStyle : uint32_t {
      Solid = XCB_LINE_STYLE_SOLID,
      OnOff = XCB_LINE_STYLE_ON_OFF_DASH
    };

  private:
#if RWL_PLATFORM == LINUX
    xcb_gcontext_t m_pen;
    Color m_fgColor, m_bgColor;
    static uint32_t s_valueMask;
    uint32_t m_lineWidth;
    LineStyle m_lineStyle;
#endif

  private:
    void create();
    void change();

  public:
    /****************************** Constructor *******************************/
    Pen(Pen &&other);
    Pen(const Pen &other);
    Pen(const Color &fgColor = Color::Black,
        const Color &bgColor = Color::Black, const uint32_t &lineWidth = 1,
        const LineStyle &lineStyle = LineStyle::Solid);

    /******************************* Operators ********************************/
    Pen &operator=(const Pen &other);

    inline Pen &operator=(const Color::ColorEnum &fgColor) {
      return this->setFgColor(fgColor);
    }
    inline Pen &operator=(const uint32_t &lineWidth) {
      return this->setLineWidth(lineWidth);
    }
    inline Pen &operator=(const LineStyle &lineStyle) {
      return this->setLineStyle(lineStyle);
    }

    /******************************** Getters *********************************/
    inline const Color &getFgColor() const {
      impl::log("Returning fg color as ", this->m_fgColor.colorToStr());
      return this->m_fgColor;
    }
    inline const Color &getBgColor() const {
      impl::log("Returning bg color as ", this->m_bgColor.colorToStr());
      return this->m_bgColor;
    }
    inline const uint32_t &getLineWidth() const {
      impl::log("Returning line width as ", this->m_lineWidth);
      return this->m_lineWidth;
    }
    inline const LineStyle &getLineStyle() const {
      impl::log("Returning line style as ",
                static_cast<uint32_t>(this->m_lineStyle));
      return this->m_lineStyle;
    }

    /******************************** Setters *********************************/
    Pen &setFgColor(const Color &fgColor);
    Pen &setLineWidth(const uint32_t &lineWidth);
    Pen &setLineStyle(const LineStyle &lineStyle);
    Pen &setColors(const Color &fgColor, const Color &bgColor);
    Pen &setLineProps(const uint32_t &lineWidth, const LineStyle &lineStyle);
    Pen &setAllProps(const Color &fgColor, const Color &bgColor,
                     const uint32_t &lineWidth, const LineStyle &lineStyle);

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
    inline const xcb_gcontext_t getP() const {
      impl::log("Returning pen with id: ", m_pen);
      return this->m_pen;
    }
#endif

    ~Pen();
  };
} // namespace rwl
