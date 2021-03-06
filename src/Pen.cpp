#include "rwl/Pen.hpp"
#include "rwl/core.hpp"

/*
 * All Functions defined here are in the order they're declared in the hpp file
 */

#define CREATE_PEN_MASK                                                        \
  uint32_t penMask[] = {this->m_fgColor.m_color, this->m_bgColor.m_color,      \
                        this->m_lineWidth,                                     \
                        static_cast<uint32_t>(this->m_lineStyle), 0}

namespace rwl {
  uint32_t Pen::s_valueMask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND |
                              XCB_GC_LINE_WIDTH | XCB_GC_LINE_STYLE |
                              XCB_GC_GRAPHICS_EXPOSURES;

  /*************************** Private Functions ***************************/
  Pen &Pen::change() {
#if RWL_PLATFORM == LINUX
    CREATE_PEN_MASK;

    xcb_change_gc(impl::core::conn, this->m_pen, this->s_valueMask, penMask);

    impl::log("Pen", "Changed fg color --> ", this->m_fgColor.colorToStr(),
              ", bg color --> ", this->m_bgColor.colorToStr(),
              ", line width --> ", this->m_lineWidth, " and line style --> ",
              static_cast<uint32_t>(this->m_lineStyle));
#endif
    return *this;
  }

  void Pen::updateVars(const Color &fgColor, const Color &bgColor,
                       const uint32_t &lineWidth, const LineStyle &lineStyle) {
    this->m_fgColor = fgColor;
    this->m_bgColor = bgColor;
    this->m_lineWidth = lineWidth;
    this->m_lineStyle = lineStyle;
  }

  /******************************* Constructors *******************************/
  Pen::Pen(Pen &&other) // Move Constructor
      : m_pen(other.m_pen) {
    updateVars(other.m_fgColor, other.m_bgColor, other.m_lineWidth,
               other.m_lineStyle);
    other.m_pen = 0;
    impl::log("Pen", "Move Constructed");
    ;
  }

  Pen::Pen(const Pen &other)
      : Pen(other.m_fgColor, other.m_bgColor, other.m_lineWidth,
            other.m_lineStyle) {}

  Pen::Pen(const LineStyle &lineStyle)
      : Pen(Color::Black, Color::Black, 1, lineStyle) {}

  Pen::Pen(const uint32_t &lineWidth, const LineStyle &lineStyle)
      : Pen(Color::Black, Color::Black, lineWidth, lineStyle) {}

  Pen::Pen(const Color &color, const uint32_t &lineWidth,
           const LineStyle &lineStyle)
      : Pen(color, color, lineWidth, lineStyle) {}

  Pen::Pen(const Color &fgColor, const Color &bgColor,
           const uint32_t &lineWidth, const LineStyle &lineStyle)
      : m_pen(xcb_generate_id(impl::core::conn)), m_fgColor(fgColor),
        m_bgColor(bgColor), m_lineWidth(lineWidth), m_lineStyle(lineStyle) {
#if RWL_PLATFORM == LINUX
    CREATE_PEN_MASK;

    xcb_create_gc(rwl::impl::core::conn, this->m_pen, impl::core::scr->root,
                  this->s_valueMask, penMask);

    impl::log("Pen", "Created");
    ;
#endif
  }

  /******************************** Operators ********************************/
  Pen &Pen::operator=(const Pen &other) {
    return this->setAllProps(other.m_fgColor, other.m_bgColor,
                             other.m_lineWidth, other.m_lineStyle);
  }

  Pen &Pen::operator=(Pen &&other) {
    if (!(other.m_pen == this->m_pen)) {
      xcb_free_gc(impl::core::conn, this->m_pen);

      updateVars(other.m_fgColor, other.m_bgColor, other.m_lineWidth,
                 other.m_lineStyle);

      this->m_pen = other.m_pen;
      other.m_pen = 0;

      impl::log("Pen", "Moved Assigned");
      ;
    }

    return *this;
  }

  bool Pen::operator==(const Pen &other) {
    return (this->m_fgColor == other.m_fgColor &&
            this->m_bgColor == other.m_bgColor &&
            this->m_lineWidth == other.m_lineWidth &&
            this->m_lineStyle == other.m_lineStyle);
  }

  /********************************* Setters *********************************/
  Pen &Pen::setFgColor(const Color &fgColor) {
    this->m_fgColor = fgColor;
    return this->change();
  }

  Pen &Pen::setBgColor(const Color &bgColor) {
    this->m_bgColor = bgColor;
    return this->change();
  }

  Pen &Pen::setColors(const Color &fgColor, const Color &bgColor) {
    this->m_fgColor = fgColor;
    this->m_bgColor = bgColor;
    return this->change();
  }

  Pen &Pen::setLineWidth(const uint32_t &lineWidth) {
    this->m_lineWidth = lineWidth;
    return this->change();
  }

  Pen &Pen::setLineStyle(const LineStyle &lineStyle) {
    this->m_lineStyle = lineStyle;
    return this->change();
  }

  Pen &Pen::setLineProps(const uint32_t &lineWidth,
                         const LineStyle &lineStyle) {
    this->m_lineWidth = lineWidth;
    this->m_lineStyle = lineStyle;
    return this->change();
  }

  Pen &Pen::setAllProps(const Color &fgColor, const Color &bgColor,
                        const uint32_t &lineWidth, const LineStyle &lineStyle) {
    updateVars(fgColor, bgColor, lineWidth, lineStyle);
    return this->change();
  }

  Pen::~Pen() {
#if RWL_PLATFORM == LINUX
    xcb_free_gc(impl::core::conn, m_pen);
#endif
    impl::log("Pen", "Destroyed.");
  }
} // namespace rwl
