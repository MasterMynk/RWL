#include "Window.hpp"
#include "rwl/core/core.hpp"

namespace rwl {
  void Window::createWin() const {
#if RWL_PLATFORM == LINUX
    uint32_t props = this->m_bgColor.m_color;

    xcb_create_window(impl::core::conn, impl::core::scr->root_depth, m_win,
                      impl::core::scr->root, this->m_pos.x, this->m_pos.y,
                      this->m_dim.width, this->m_dim.height, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      impl::core::scr->root_visual, XCB_CW_BACK_PIXEL, &props);
#endif
  }

  Window::Window(Window &&other)
      : m_win(other.m_win), m_dim(other.m_dim), m_pos(other.m_pos),
        m_bgColor(other.m_bgColor) {
    other.m_win = 0;
  }

  Window::Window(const Window &other)
      : m_win(xcb_generate_id(impl::core::conn)), m_dim(other.m_dim),
        m_pos(other.m_pos), m_bgColor(other.m_bgColor) {
    createWin();
  }

  Window::Window(const Dim &dim, const Pos &pos, const Color &bgColor)
      : m_win(xcb_generate_id(impl::core::conn)), m_dim(dim), m_pos(pos),
        m_bgColor(bgColor) {
    createWin();
  }

  Window &Window::operator=(const Window &other) {
    setPos(other.m_pos);
    setDim(other.m_dim);

    return *this;
  }

  Window &Window::show() {
    showNoUpdate();
    update();

    return *this;
  }

  Window &Window::showNoUpdate() {
    xcb_map_window(impl::core::conn, m_win);

    return *this;
  }

  Window &Window::hide() {
    hideNoUpdate();
    update();

    return *this;
  }

  Window &Window::hideNoUpdate() {
    xcb_unmap_window(impl::core::conn, m_win);

    return *this;
  }

  Window::~Window() { xcb_destroy_window(impl::core::conn, m_win); }
} // namespace rwl
