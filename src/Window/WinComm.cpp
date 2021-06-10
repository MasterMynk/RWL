#include "rwl/Window/WinComm.hpp"
#include "rwl/core.hpp"

namespace rwl::impl {
  WinComm::WinComm(const xcb_window_t &winId, const Pos &pos, const Dim &dim,
                   const Color &bgColor)
      : m_win(winId), m_pos(pos), m_dim(dim), m_bgColor(bgColor) {
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

  WinComm &WinComm::operator=(const WinComm &other) {
    setDim(other.m_dim);
    setPos(other.m_pos);

    impl::log("Set window dim and pos to ", this->m_dim, this->m_pos);

    return *this;
  }

  WinComm &WinComm::show() {
    showNoUpdate();
    update();

    impl::log("Don't worry I called update.");

    return *this;
  }

  WinComm &WinComm::showNoUpdate() {
    xcb_map_window(impl::core::conn, m_win);

    impl::log("Mapped window. Better call update if you haven't already!");

    return *this;
  }

  WinComm &WinComm::hide() {
    hideNoUpdate();
    update();

    impl::log("Don't worry I called update.");

    return *this;
  }

  WinComm &WinComm::hideNoUpdate() {
    xcb_unmap_window(impl::core::conn, m_win);

    impl::log("Unmapped WinComm. Call update if you haven't already.");

    return *this;
  }
} // namespace rwl::impl