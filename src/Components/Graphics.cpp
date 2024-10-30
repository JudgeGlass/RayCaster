#include "Components/Graphics.hpp"

Graphics::Graphics(const uint32_t x, const uint32_t y, const uint32_t bitmap_width, const uint32_t bitmap_height)
    : m_width(bitmap_width), m_height(bitmap_height)
{
  m_x = x;
  m_y = y;

  m_bitmap = new uint32_t[m_width * m_height];

  m_bitmap_texture = SDL_CreateTexture((SDL_Renderer *)WindowMgr::get_instance().get_renderer()->get_sdl_renderer(),
      SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

  clear_buffer();
}

Graphics::~Graphics()
{
  delete[] m_bitmap;
}

void Graphics::update()
{
  if (m_on_update)
  {
    m_on_update();
  }
}

void Graphics::render()
{
  if (m_on_redraw)
  {
    m_on_redraw();
  }

  auto renderer = WindowMgr::get_instance().get_renderer();
  for (int x = 0; x < m_width; x++)
  {
    for (int y = 0; y < m_height; y++)
    {
      renderer->render_color(m_bitmap[x + y * m_width]);
      SDL_RenderDrawPoint((SDL_Renderer *)renderer->get_sdl_renderer(), x + m_x, y + m_y);
    }
  }
}

void Graphics::set_pixel(int x, int y, int color)
{
  if (x >= 0 && x < m_width && y >= 0 && y < m_height)
  {
    m_bitmap[x + y * m_width] = color;
  }
}

bool Graphics::is_enabled() const {}

void Graphics::on_click(std::function<void()> func) {}

void Graphics::clear_buffer()
{
  for (int i = 0; i < m_width * m_height; i++)
  {
    m_bitmap[i] = 0;
  }
}

void Graphics::on_redraw(std::function<void()> func)
{
  m_on_redraw = func;
}

void Graphics::on_update(std::function<void()> func)
{
  m_on_update = func;
}