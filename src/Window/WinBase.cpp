#include "rwl/Window/WinBase.hpp"

namespace rwl::impl {
  /******************************* Constructors *******************************/
  WinBase::WinBase(const xcb_window_t &winId, const PosDim &posDim,
                   const Color &bgColor)
      : m_win(winId), m_posDim(posDim), m_bgColor(bgColor) {}

  /******************************** Operators ********************************/
  WinBase &WinBase::operator=(const WinBase &other) {
    this->setDim(other.m_posDim.dim);
    this->setPos(other.m_posDim.pos);

    impl::log("Window", "Dim = ", this->m_posDim.dim,
              "Pos = ", this->m_posDim.pos);

    return *this;
  }

  /******************************** Functions ********************************/
  WinBase &WinBase::show() {
    this->showNoUpdate();
    update();

    impl::log("Window", "Shown");

    return *this;
  }

  WinBase &WinBase::showNoUpdate() {
    xcb_map_window(impl::core::conn, m_win);

    impl::log("Window", "Shown without updating.");

    return *this;
  }

  WinBase &WinBase::hide() {
    this->hideNoUpdate();
    update();

    impl::log("Window", "Hidden");

    return *this;
  }

  WinBase &WinBase::hideNoUpdate() {
    xcb_unmap_window(impl::core::conn, m_win);

    impl::log("Window", "Hidden wihtout updating");

    return *this;
  }
} // namespace rwl::impl
