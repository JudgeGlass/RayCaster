#include "Components/CheckBox.hpp"

CheckBox::CheckBox(const uint32_t x, const uint32_t y, const bool checked, const std::string &label)
    : m_is_checked(checked), m_label(label)
{
  m_x = x;
  m_y = y;
}

void CheckBox::render()
{
  Compositor::get_instance().draw_checkbox(m_x, m_y, m_is_checked, m_label);
}

void CheckBox::update()
{
  if (WindowMgr::get_instance().m_mouse1_pressed)
  {
    if (Component::is_in_bounds(WindowMgr::get_instance().get_mouse_pos().first,
            WindowMgr::get_instance().get_mouse_pos().second, m_x, m_y, m_width, m_height))
    {
      m_is_checked = !m_is_checked;
      if (m_event_func)
      {
        m_event_func();
      }
    }
  }
}

void CheckBox::on_click(std::function<void()> event)
{
  m_event_func = event;
}

bool CheckBox::is_enabled() const
{
  return m_is_checked;
}