#include "rwl/Window/Window.hpp"

namespace rwl {
  /************************* Private Member Functions *************************/
  void Window::create() {
#if RWL_PLATFORM == LINUX
    uint32_t props[2] = {this->m_bgColor.m_color, XCB_EVENT_MASK_EXPOSURE};

    xcb_create_window(impl::core::conn, impl::core::scr->root_depth, m_win,
                      m_parent.m_win, this->m_pos.x, this->m_pos.y,
                      this->m_dim.width, this->m_dim.height,
                      this->m_borderWidth, XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      impl::core::scr->root_visual,
                      XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, &props);
    impl::log("Created a window with window Id: ", m_win);
#endif
  }

  /******************************* Constructors *******************************/
  Window::Window(Window &&other)
      : WinComm(other.m_win, other.m_pos, other.m_dim, other.m_bgColor),
        m_parent(other.m_parent), m_borderWidth(other.m_borderWidth) {
    impl::log("Moved a window with window Id: ", m_win);
    other.m_win = 0;
  }

  Window::Window(const Window &other)
      : Window(other.m_pos, other.m_dim, other.m_bgColor, other.m_parent,
               other.m_borderWidth) {}

  Window::Window(const Pos &pos, const Dim &dim, const Color &bgColor,
                 const WinComm &parent, const uint16_t &borderWidth)
      : WinComm(xcb_generate_id(impl::core::conn), pos, dim, bgColor),
        m_parent(parent), m_borderWidth(borderWidth) {
    create();
  }

  Window::~Window() {
#if RWL_PLATFORM == LINUX
    xcb_destroy_window(impl::core::conn, m_win);
#endif
    impl::log("Window Destroyed");
  }
} // namespace rwl