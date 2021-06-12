#pragma once
#include "rwl/Color.hpp"
#include "rwl/Log.hpp"
#include <xcb/xcb.h>

namespace rwl {
  namespace impl {
    template <typename T>
    class RectPtrComm;

    template <typename T>
    class RectRefComm;
  } // namespace impl

  class Pen {
  public:
    enum class LineStyle : uint32_t {
      Solid = XCB_LINE_STYLE_SOLID,
      Dash = XCB_LINE_STYLE_ON_OFF_DASH
    };

  private:
#if RWL_PLATFORM == LINUX
    xcb_gcontext_t m_pen;
    Color m_fgColor, m_bgColor;
    uint32_t m_lineWidth;
    LineStyle m_lineStyle;

    static uint32_t s_valueMask;
#endif

  private:
    Pen &change();
    void updateVars(const Color &fgColor, const Color &bgColor,
                    const uint32_t &lineWidth, const LineStyle &lineStyle);

  public:
    /****************************** Constructor *******************************/
    Pen(Pen &&other);
    Pen(const Pen &other);
    Pen(const Color &color = Color::Black, const uint32_t &lineWidth = 1,
        const LineStyle &lineStyle = LineStyle::Solid);
    Pen(const Color &fgColor, const Color &bgColor,
        const uint32_t &lineWidth = 1,
        const LineStyle &lineStyle = LineStyle::Solid);

    /******************************* Operators ********************************/
    Pen &operator=(const Pen &other);
    Pen &operator=(Pen &&other);

    inline Pen &operator=(const Color::ColorEnum &colors) {
      return this->setColors(colors);
    }
    inline Pen &operator=(const uint32_t &lineWidth) {
      return this->setLineWidth(lineWidth);
    }
    inline Pen &operator=(const LineStyle &lineStyle) {
      return this->setLineStyle(lineStyle);
    }

    /******************************** Getters *********************************/
    inline const Color &getFgColor() const {
      impl::log<impl::LogLevel::NoImp>("Returning fg color as ",
                                       this->m_fgColor.colorToStr());
      return this->m_fgColor;
    }
    inline const Color &getBgColor() const {
      impl::log<impl::LogLevel::NoImp>("Returning bg color as ",
                                       this->m_bgColor.colorToStr());
      return this->m_bgColor;
    }
    inline const uint32_t &getLineWidth() const {
      impl::log<impl::LogLevel::NoImp>("Returning line width as ",
                                       this->m_lineWidth);
      return this->m_lineWidth;
    }
    inline const LineStyle &getLineStyle() const {
      impl::log<impl::LogLevel::NoImp>(
          "Returning line style as ", static_cast<uint32_t>(this->m_lineStyle));
      return this->m_lineStyle;
    }

    /******************************** Setters *********************************/
    Pen &setFgColor(const Color &fgColor);
    Pen &setBgColor(const Color &bgColor);
    inline Pen &setColors(const Color &colors) {
      return this->setColors(colors, colors);
    }
    Pen &setColors(const Color &fgColor, const Color &bgColor);
    Pen &setLineWidth(const uint32_t &lineWidth);
    Pen &setLineStyle(const LineStyle &lineStyle);
    Pen &setLineProps(const uint32_t &lineWidth, const LineStyle &lineStyle);
    inline Pen &setAllProps(const Color &colors, const uint32_t &lineWidth,
                            const LineStyle &lineStyle) {
      return this->setAllProps(colors, colors, lineWidth, lineStyle);
    }
    Pen &setAllProps(const Color &fgColor, const Color &bgColor,
                     const uint32_t &lineWidth, const LineStyle &lineStyle);

#if RWL_PLATFORM == LINUX && RWL_DEBUG == 1
    inline const xcb_gcontext_t getP() const {
      impl::log<impl::LogLevel::NoImp>("Returning pen with id: ", m_pen);
      return this->m_pen;
    }
#endif

    ~Pen();

    template <typename T>
    friend class impl::RectPtrComm;

    template <typename T>
    friend class impl::RectRefComm;
  };
} // namespace rwl
