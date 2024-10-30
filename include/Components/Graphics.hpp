#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "../Compositor.hpp"
#include "WindowComponent.hpp"
#include <functional>

class Graphics : public WindowComponent
{
public:
public:
  Graphics(const uint32_t x, const uint32_t y, const uint32_t bitmap_width, const uint32_t bitmap_height);
  ~Graphics();

  void update() override;
  void render() override;

  void set_pixel(int x, int y, int color);
  void clear_buffer();

  bool is_enabled() const;

  void on_click(std::function<void()> func);
  void on_redraw(std::function<void()> func);
  void on_update(std::function<void()> func);

private:
private:
  uint32_t m_width{16};
  uint32_t m_height{16};
  uint32_t *m_bitmap;

  // void (*m_event_func)(){nullptr};
  std::function<void()> m_event_func;
  std::function<void()> m_on_redraw;
  std::function<void()> m_on_update;

  SDL_Texture *m_bitmap_texture;
};

#endif