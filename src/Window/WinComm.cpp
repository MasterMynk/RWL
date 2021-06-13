#include "rwl/Window/WinComm.hpp"
#include "rwl/core.hpp"

namespace rwl::impl {
  /******************************* Constructors *******************************/
  WinComm::WinComm(const xcb_window_t &winId, const Pos &pos, const Dim &dim,
                   const Color &bgColor)
      : m_win(winId), m_pos(pos), m_dim(dim), m_bgColor(bgColor) {}

  /******************************** Operators ********************************/
  WinComm &WinComm::operator=(const WinComm &other) {
    this->setDim(other.m_dim);
    this->setPos(other.m_pos);

    impl::log("Set window dim and pos to ", this->m_dim, this->m_pos);

    return *this;
  }

  /******************************** Functions ********************************/
  WinComm &WinComm::show() {
    this->showNoUpdate();
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
    this->hideNoUpdate();
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
