#include "rwl/Window/Window.hpp"
#include "rwl/core.hpp"

namespace rwl {
  Window::Window(Window &&other)
      : WinComm(other.m_win, other.m_pos, other.m_dim, other.m_bgColor) {
    impl::log("Moved a window with window Id: ", m_win);
    other.m_win = 0;
  }

  Window::Window(const Window &other)
      : WinComm(xcb_generate_id(impl::core::conn), other.m_pos, other.m_dim,
                other.m_bgColor) {}

  Window::Window(const Pos &pos, const Dim &dim, const Color &bgColor)
      : WinComm(xcb_generate_id(impl::core::conn), pos, dim, bgColor) {}

  Window::~Window() {
#if RWL_PLATFORM == LINUX
    xcb_destroy_window(impl::core::conn, m_win);
#endif
    impl::log("Window Destroyed");
  }
} // namespace rwl