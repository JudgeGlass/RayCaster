#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../Compositor.hpp"
#include "../Renderer.hpp"
#include "WindowComponent.hpp"
#include <functional>

class Button : public WindowComponent
{
public:
public:
  Button(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height, const std::string &text);

  void update() override;
  void render() override;

  void on_click(std::function<void()> func);
  void push_handler();

private:
private:
  uint32_t m_width;
  uint32_t m_height;
  std::string m_text;

  // void (*m_event_func)(){nullptr};
  std::function<void()> m_event_func;

  uint32_t m_push_time{0};
  bool m_pushed{false};
};

#endif