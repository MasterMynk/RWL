#include "rwl/Window/Window.hpp"

namespace rwl {
  /******************************* Helper Ctors *******************************/
  Window::Window(const xcb_window_t &win, const PosDim &pd, const Color &bg,
                 const impl::WinBase &parent, const uint16_t &borderWidth,
                 const Color &borderColor)
      : WinBase(win, pd, bg), m_parent(parent), m_borderWidth(borderWidth),
        m_borderColor(borderColor) {}

  /********************************* Helpers *********************************/
  void Window::create() {
#if RWL_PLATFORM == LINUX
    uint32_t props[] = {this->m_bgColor.m_color, this->m_borderColor.m_color,
                        XCB_EVENT_MASK_EXPOSURE};

    xcb_create_window(
        impl::core::conn, impl::core::scr->root_depth, m_win, m_parent.m_win,
        this->m_posDim.pos.x, this->m_posDim.pos.y, this->m_posDim.dim.width,
        this->m_posDim.dim.height, this->m_borderWidth,
        XCB_WINDOW_CLASS_INPUT_OUTPUT, impl::core::scr->root_visual,
        XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK, &props);
    impl::log("Window", "Created with Id: ", m_win);
#endif
  }

  /********************************** Ctors **********************************/
  Window::Window(Window &&other)
      : Window(other.m_win, other.m_posDim, other.m_bgColor, other.m_parent,
               other.m_borderWidth, other.m_borderColor) {
    impl::log("Window", "Moved.");
    other.m_win = 0;
  }

  Window::Window(const Window &other)
      : Window(other.m_posDim, other.m_bgColor, other.m_parent,
               other.m_borderWidth, other.m_borderColor) {}

  Window::Window(const PosDim &posDim, const Color &bgColor,
                 const WinBase &parent, const uint16_t &borderWidth,
                 const Color &borderColor)
      : Window(xcb_generate_id(impl::core::conn), posDim, bgColor, parent,
               borderWidth, borderColor) {
    this->create();
    this->show();
  }

  Window::~Window() {
#if RWL_PLATFORM == LINUX
    xcb_destroy_window(impl::core::conn, m_win);
#endif
    impl::log("Window", "Destroyed");
  }
} // namespace rwl