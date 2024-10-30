#include "Compositor.hpp"

void Compositor::draw_window_frame(
    const int &window_x, const int &window_y, const uint32_t &window_width, const uint32_t &window_height)
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_color(0xC0, 0xC0, 0xC0);
  renderer->render_rect(window_x, window_y, window_width, window_height, true);

  renderer->render_color(0xFF, 0xFF, 0xFF);
  renderer->render_rect(window_x + 1, window_y + 1, window_width - 2, window_height - 2, false);

  renderer->render_color(0, 0x0C, 0x75);
  renderer->render_rect(window_x + 4, window_y + 4, window_width - 8, 24, true);
}

void Compositor::draw_button_normal(
    const int &x, const int &y, const uint32_t &width, const uint32_t &height, const std::string &text)
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_color(0, 0, 0);
  renderer->render_rect(x, y, width, height, false);
  renderer->render_color(0xFF, 0xFF, 0xFF);
  renderer->render_rect(x, y, width - 1, height - 1, false);
  renderer->render_color(0x80, 0x80, 0x80);
  renderer->render_rect(x + 1, y + 1, width - 2, height - 2, false);
  renderer->render_color(0xC0, 0xC0, 0xC0);
  renderer->render_rect(x + 1, y + 1, width - 2, height - 2, true);

  renderer->draw_string(x + (width / 2) - 8 * (text.size() / 2), y + 8, text, 0, 1);
}

void Compositor::draw_button_pushed(
    const int &x, const int &y, const uint32_t &width, const uint32_t &height, const std::string &text)
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_color(0, 0, 0);
  renderer->render_rect(x, y, width, height, true);
  renderer->render_color(0xFF, 0xFF, 0xFF);
  renderer->render_rect(x + 1, y + 1, width - 1, height - 1, true);
  renderer->render_color(0x80, 0x80, 0x80);
  renderer->render_rect(x + 1, y + 1, width - 2, height - 2, true);
  renderer->render_color(0xC0, 0xC0, 0xC0);
  renderer->render_rect(x + 2, y + 2, width - 3, height - 3, true);

  renderer->draw_string(x + (width / 2) - 8 * (text.size() / 2), y + 8, text, 0, 1);
}

void Compositor::draw_checkbox(const int &x, const int &y, bool is_checked, const std::string &text)
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  renderer->render_texture((is_checked ? 10 : 9), x, y, 1, 16);
  renderer->draw_string(x + 20, y + 4, text, 0, 1);
}

void Compositor::draw_input_buffer(const int &x, const int &y, const int &cols, const int &rows, const char *buffer)
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  int width = cols * 8 + 10;
  int height = rows * 8 + 10;

  renderer->render_color(0xFF, 0xFF, 0xFF);
  renderer->render_rect(x, y, width, height, true);

  renderer->render_color(0x80, 0x80, 0x80);
  renderer->render_rect(x, y, width, height, false);

  renderer->render_color(0xC0, 0xC0, 0xC0);
  renderer->render_rect(x + 1, y, width - 2, height, false);

  renderer->render_color(0x0, 0x0, 0x0);
  renderer->render_rect(x + 2, y + 1, width - 3, height - 2, false);
}
