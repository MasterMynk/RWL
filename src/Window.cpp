#include "rwl/Window.hpp"
#include "rwl/core.hpp"

namespace rwl {
  Window::Window(Window &&other)
      : m_win(other.m_win), m_dim(other.m_dim), m_pos(other.m_pos),
        m_bgColor(other.m_bgColor) {
    impl::log("Moved a window with window Id: ", m_win);
    other.m_win = 0;
  }

  Window::Window(const Window &other) {
    Window(other.m_pos, other.m_dim, other.m_bgColor);
  }

  Window::Window(const Pos &pos, const Dim &dim, const Color &bgColor)
      : m_win(xcb_generate_id(impl::core::conn)), m_pos(pos), m_dim(dim),
        m_bgColor(bgColor) {
#if RWL_PLATFORM == LINUX
    uint32_t props[2] = {this->m_bgColor.m_color, XCB_EVENT_MASK_EXPOSURE};

    xcb_create_window(impl::core::conn, impl::core::scr->root_depth, m_win,
                      impl::core::scr->root, this->m_pos.x, this->m_pos.y,
                      this->m_dim.width, this->m_dim.height, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      impl::core::scr->root_visual,
                      XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, &props);
    impl::log("Created a window with window Id: ", m_win);
#endif
  }

  Window &Window::operator=(const Window &other) {
    setDim(other.m_dim);
    setPos(other.m_pos);

    impl::log("Set window dim and pos to ", this->m_dim, this->m_pos);

    return *this;
  }

  Window &Window::show() {
    showNoUpdate();
    update();

    impl::log("Don't worry I called update.");

    return *this;
  }

  Window &Window::showNoUpdate() {
    xcb_map_window(impl::core::conn, m_win);

    impl::log("Mapped window. Better call update if you haven't already!");

    return *this;
  }

  Window &Window::hide() {
    hideNoUpdate();
    update();

    impl::log("Don't worry I called update.");

    return *this;
  }

  Window &Window::hideNoUpdate() {
    xcb_unmap_window(impl::core::conn, m_win);

    impl::log("Unmapped Window. Call update if you haven't already.");

    return *this;
  }

  Window::~Window() {
#if RWL_PLATFORM == LINUX
    xcb_destroy_window(impl::core::conn, m_win);
#endif
    impl::log("Window Destroyed");
  }
} // namespace rwl
