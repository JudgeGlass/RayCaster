#ifndef COMPOSITOR_HPP
#define COMPOSITOR_HPP

#include "Singleton.hpp"
#include "WindowMgr.hpp"

class Compositor : public Singleton<Compositor>
{
  friend class Singleton<Compositor>;

public:
public:
  void draw_window_frame(
      const int &window_x, const int &window_y, const uint32_t &window_width, const uint32_t &window_height);
  void draw_button_normal(
      const int &x, const int &y, const uint32_t &width, const uint32_t &height, const std::string &text);

  void draw_button_pushed(
      const int &x, const int &y, const uint32_t &width, const uint32_t &height, const std::string &text);
  void draw_checkbox(const int &x, const int &y, bool is_checked, const std::string &text);
  void draw_input_buffer(const int &x, const int &y, const int &cols, const int &rows, const char *buffer);

private:
private:
};

#endif