#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Singleton.hpp"
#include "Texture.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <memory>

class Renderer
{
public:
public:
  Renderer(const SDL_Window *window, const SDL_Renderer *renderer);

  void render_color(const uint8_t r, const uint8_t g, const uint8_t b);
  void render_color(int color);
  void render_rect(const int x, const int y, const int w, const int h, bool filled);
  void render_backdrop(const int x, const int y, const int w, const int h);
  void render_texture(const int index, const int x, const int y, const int scale, const int rowa);
  void draw_string(int x, int y, std::string text, int color, int scale);
  void draw_string_shadowed(int x, int y, std::string text, int color, int scale);
  void draw_line(const int x1, const int y1, const int x2, const int y2);
  int get_texture_pixel(int tile, int col_x, int y, int rowa);

  const SDL_Renderer *get_sdl_renderer() const;

private:
  std::string font_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ|*^   0123456789.,!?'\"-+=/\\%()<>:;_   abcdefghijklmnopqrstuvwxyz█     ";

  const SDL_Window *m_sdl_window;
  const SDL_Renderer *m_sdl_renderer;
  std::unique_ptr<Texture> m_ui_textures;
  std::unique_ptr<Texture> m_ui_font_textures;
  std::unique_ptr<Texture> m_block_textures;

private:
};

#endif