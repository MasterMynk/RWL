#include "Window.hpp"

namespace rwl {
  void Window::createWin() const {
    uint32_t winProps = core::scr->white_pixel;

    xcb_create_window(core::conn, core::scr->root_depth, m_win, core::scr->root,
                      this->m_pos.x, this->m_pos.y, this->m_dim.width,
                      this->m_dim.height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      core::scr->root_visual, XCB_CW_BACK_PIXEL, &winProps);
  }

  Window::Window(const Dim &dim, const Pos &pos)
      : m_win(xcb_generate_id(core::conn)), m_dim(dim), m_pos(pos) {
    createWin();
  }

  Window::Window(const Window &other)
      : m_win(xcb_generate_id(core::conn)), m_dim(other.m_dim),
        m_pos(other.m_pos) {
    createWin();
  }

  Window::Window(Window &&other)
      : m_win(other.m_win), m_dim(other.m_dim), m_pos(other.m_pos) {
    other.m_win = 0;
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
    xcb_map_window(core::conn, m_win);

    return *this;
  }

  Window &Window::hide() {
    hideNoUpdate();
    update();

    return *this;
  }

  Window &Window::hideNoUpdate() {
    xcb_unmap_window(core::conn, m_win);

    return *this;
  }

  Window::~Window() { xcb_destroy_window(core::conn, m_win); }
} // namespace rwl
