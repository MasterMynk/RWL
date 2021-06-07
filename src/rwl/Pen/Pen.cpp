#include "Pen.hpp"
#include "rwl/core/core.hpp"

#define CREATE_PEN_MASK                                                        \
  uint32_t penMask[] = {this->m_fgColor.m_color, this->m_bgColor.m_color,      \
                        this->m_lineWidth, 0}
#define LOGGING_HELPER(x)                                                      \
  impl::log("Pen ", (x), ": fg color --> ", this->m_fgColor.colorToStr(),      \
            ", bg color --> ", this->m_bgColor.colorToStr(),                   \
            " and line width --> ", this->m_lineWidth)

namespace rwl {
  uint32_t Pen::s_valueMask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND |
                              XCB_GC_LINE_WIDTH | XCB_GC_GRAPHICS_EXPOSURES;

  void Pen::create() {
#if RWL_PLATFORM == LINUX
    CREATE_PEN_MASK;

    xcb_create_gc(rwl::impl::core::conn, this->m_pen, impl::core::scr->root,
                  this->s_valueMask, penMask);

    LOGGING_HELPER("Created");
#endif
  }

  void Pen::change() {
#if RWL_PLATFORM == LINUX
    CREATE_PEN_MASK;

    xcb_change_gc(impl::core::conn, this->m_pen, this->s_valueMask, penMask);

    LOGGING_HELPER("Changed");
#endif
  }

  Pen::Pen(Pen &&other)
      : m_pen(other.m_pen), m_fgColor(other.m_fgColor),
        m_bgColor(other.m_bgColor), m_lineWidth(other.m_lineWidth) {
    other.m_pen = 0;
    LOGGING_HELPER("Moved");
  }

  Pen::Pen(const Pen &other)
      : m_pen(xcb_generate_id(impl::core::conn)), m_fgColor(other.m_fgColor),
        m_bgColor(other.m_bgColor), m_lineWidth(other.m_lineWidth) {
    this->create();
  }

  Pen::Pen(const Color &fgColor, const Color &bgColor,
           const uint32_t &lineWidth)
      : m_pen(xcb_generate_id(impl::core::conn)), m_fgColor(fgColor),
        m_bgColor(bgColor), m_lineWidth(lineWidth) {
    this->create();
  }

  Pen &Pen::operator=(const Pen &other) {
    return this->setAllProps(other.m_fgColor, other.m_bgColor,
                             other.m_lineWidth);
  }

  Pen &Pen::setFgColor(const Color &fgColor) {
    this->m_fgColor = fgColor;
    this->change();

    return *this;
  }

  Pen &Pen::setLineWidth(const uint32_t &lineWidth) {
    this->m_lineWidth = lineWidth;
    change();

    return *this;
  }

  Pen &Pen::setColors(const Color &fgColor, const Color &bgColor) {
    this->m_fgColor = fgColor;
    this->m_bgColor = bgColor;
    this->change();

    return *this;
  }

  Pen &Pen::setAllProps(const Color &fgColor, const Color &bgColor,
                        const uint32_t &lineWidth) {
    this->m_fgColor = fgColor;
    this->m_bgColor = bgColor;
    this->m_lineWidth = lineWidth;
    this->change();

    return *this;
  }

  Pen::~Pen() {
#if RWL_PLATFORM == LINUX
    xcb_free_gc(impl::core::conn, m_pen);
#endif
    impl::log("Pen Destroyed.");
  }
} // namespace rwl
