#include "Components/Button.hpp"

Button::Button(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &text)
    : m_width(width), m_height(height), m_text(text)
{
  m_x = x;
  m_y = y;
}

void Button::render()
{
  if (m_enabled && !m_pushed)
  {
    Compositor::get_instance().draw_button_normal(m_x, m_y, m_width, m_height, m_text);
  }
  else
  {
    Compositor::get_instance().draw_button_pushed(m_x, m_y, m_width, m_height, m_text);
  }
}

void Button::push_handler()
{
  if (m_push_time > 0)
  {
    m_push_time--;
  }
  else
  {
    m_pushed = false;
  }
}

void Button::update()
{
  push_handler();
  if (WindowMgr::get_instance().m_mouse1_pressed)
  {
    if (Component::is_in_bounds(WindowMgr::get_instance().get_mouse_pos().first,
            WindowMgr::get_instance().get_mouse_pos().second, m_x, m_y, m_width, m_height))
    {
      m_pushed = true;
      m_push_time = 5;

      if (m_event_func)
      {
        m_event_func();
      }
    }
  }
}

void Button::on_click(std::function<void()> event)
{
  m_event_func = event;
}