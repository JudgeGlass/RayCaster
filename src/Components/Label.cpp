#include "Components/Label.hpp"

Label::Label(const uint32_t x, const uint32_t y, const std::string &label, const uint32_t color)
    : m_label(label), m_color(color)
{
  m_x = x;
  m_y = y;
}

void Label::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();
  renderer->draw_string(m_x, m_y, m_label, m_color, 1);
}

void Label::update()
{
  // m_label += WindowMgr::get_instance().get_text_input();
  // if (WindowMgr::get_instance().backspace_pressed())
  // {
  //   if (!m_label.empty())
  //     m_label.pop_back();
  // }
}