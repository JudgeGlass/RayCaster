#include "Window.hpp"

Window::Window(
    const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &title)
    : m_width(width), m_height(height), m_title(title)
{
  m_x = x;
  m_y = y;

  m_exit_btn = std::make_unique<Button>((m_x + m_width) - 8 - 16, m_y + 8, 16, 16, "");
  m_minimize_btn = std::make_unique<Button>((m_x + m_width) - 12 - 16 - 16, m_y + 8, 16, 16, "");
  m_minimize_btn->disable();

  WindowMgr::get_instance().set_focus(this);
}

void Window::add_component(WindowComponent *component)
{
  int x = component->get_x();
  int y = component->get_y();
  component->set_position(x + m_x, y + m_y);
  m_ui_components.push_back(component);
}

void Window::on_close(std::function<void()> event)
{
  m_on_close = event;
  m_exit_btn->on_click(m_on_close);
}

void Window::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();
  renderer->render_backdrop(0, 0, WindowMgr::get_instance().m_window_width, WindowMgr::get_instance().m_window_height);

  Compositor::get_instance().draw_window_frame(m_x, m_y, m_width, m_height);

  renderer->draw_string_shadowed(m_x + 8, m_y + 12, m_title, 0xFFFFFF, 1);

  m_exit_btn->render();
  renderer->render_texture(0, m_exit_btn->get_x(), m_exit_btn->get_y(), 1, 16);

  m_minimize_btn->render();
  renderer->render_texture(2, m_minimize_btn->get_x(), m_minimize_btn->get_y(), 1, 16);

  for (const auto &comp : m_ui_components)
  {
    comp->render();
  }

  if (m_window_grabbed)
  {
    renderer->render_color(0, 0, 0);
    renderer->render_rect(m_window_prev_x, m_window_prev_y, m_width, m_height, false);
  }
}

void Window::update()
{
  move();

  m_exit_btn->update();
  m_minimize_btn->update();

  for (const auto &comp : m_ui_components)
  {
    comp->update();
  }
}

void Window::move()
{
  int mouse_x = WindowMgr::get_instance().get_mouse_pos().first;
  int mouse_y = WindowMgr::get_instance().get_mouse_pos().second;
  bool mouse_clicked = WindowMgr::get_instance().m_mouse1_pressed;
  if (mouse_clicked && !m_window_grabbed && Component::is_in_bounds(mouse_x, mouse_y, m_x, m_y, m_width - 48, 26))
  {
    m_window_grabbed = true;
  }
  else if (mouse_clicked && m_window_grabbed)
  {
    m_window_grabbed = false;
    int old_mx = m_x;
    int old_my = m_y;
    m_x = m_window_prev_x;
    m_y = m_window_prev_y;
    int dx = m_x - old_mx;
    int dy = m_y - old_my;

    m_exit_btn->set_position(m_exit_btn->get_x() + dx, m_exit_btn->get_y() + dy);
    m_minimize_btn->set_position(m_minimize_btn->get_x() + dx, m_minimize_btn->get_y() + dy);

    for (const auto &comp : m_ui_components)
    {
      int x = comp->get_x();
      int y = comp->get_y();

      comp->set_position(x + dx, y + dy);
    }
  }
  else if (m_window_grabbed)
  {
    m_window_prev_x = mouse_x - (m_width / 2);
    m_window_prev_y = mouse_y;
  }
}

void Window::close()
{
  if (m_on_close)
  {
    m_on_close();
  }
}

void Window::enable_minimize_button()
{
  m_minimize_btn->enable();
}

void Window::disable_minimize_button()
{
  m_minimize_btn->disable();
}