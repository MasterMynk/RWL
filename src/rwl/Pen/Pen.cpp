#include "Pen.hpp"
#include "rwl/core/core.hpp"

namespace rwl {
  uint32_t Pen::s_valueMask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;

  void Pen::create() {
#if RWL_PLATFORM == LINUX
    uint32_t penMask[] = {this->m_fgColor.m_color, 0};

    xcb_create_gc(rwl::impl::core::conn, this->m_pen, impl::core::scr->root,
                  this->s_valueMask, penMask);

    impl::log("Created a Pen with id: ", this->m_pen);
#endif
  }

  void Pen::change() {
#if RWL_PLATFORM == LINUX
    uint32_t penMask[] = {m_fgColor.m_color, 0};

    xcb_change_gc(impl::core::conn, this->m_pen, this->s_valueMask, penMask);

    impl::log("Changed the pen to an fg color of ", m_fgColor.colorToStr());
#endif
  }

  Pen::Pen(Pen &&other) : m_pen(other.m_pen), m_fgColor(other.m_fgColor) {
    other.m_pen = 0;
    impl::log("Moved a pen with id: ", this->m_pen);
  }

  Pen::Pen(const Pen &other)
      : m_pen(xcb_generate_id(impl::core::conn)), m_fgColor(other.m_fgColor) {
    create();
    impl::log("Copy Constructed a Pen.");
  }

  Pen::Pen(const Color &fgColor)
      : m_pen(xcb_generate_id(impl::core::conn)), m_fgColor(fgColor) {
    create();
    impl::log("Constructed a Pen.");
  }

  Pen &Pen::operator=(const Pen &other) {
    impl::log("Changing fg color from", this->m_fgColor.colorToStr(), " --> ",
              other.m_fgColor.colorToStr());
    this->m_fgColor = other.m_fgColor;
    change();

    return *this;
  }

  Pen &Pen::setFgColor(const Color &fgColor) {
    impl::log("Changing fg color from ", this->m_fgColor.colorToStr(), " --> ",
              fgColor.colorToStr());
    this->m_fgColor = fgColor;
    change();

    return *this;
  }

  Pen::~Pen() {
#if RWL_PLATFORM == LINUX
    xcb_free_gc(impl::core::conn, m_pen);
#endif
    impl::log("Pen Destroyed.");
  }
} // namespace rwl
