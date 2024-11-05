#include "Texture.hpp"

Texture::Texture(std::string filename, int pw, int ph)
{
  this->filename = filename;
  this->pw = pw;
  this->ph = ph;
}

void Texture::load(SDL_Renderer *renderer)
{
  SDL_Texture *texture = IMG_LoadTexture(renderer, filename.c_str());
  if (texture == nullptr)
  {
    std::cerr << "Error loading texture: " << filename << std::endl;
  }

  std::cout << "Loaded: " << filename << std::endl;
  this->texture = texture;

  int h, w;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

void Texture::render(SDL_Renderer *renderer, int index, int x, int y, int scale, int rowa)
{
  // rowa = row amount ex. 32
  int sx = (index % rowa) * pw;
  int sy = (index / rowa) * ph;

  SDL_Rect spriteTile;
  spriteTile.x = sx;
  spriteTile.y = sy;
  spriteTile.w = pw;
  spriteTile.h = ph;

  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = pw * scale;
  dst.h = ph * scale;

  SDL_RenderCopy(renderer, texture, &spriteTile, &dst);
}

int Texture::get_pixel(SDL_Renderer *renderer, int tile, int col_x, int y, int rowa)
{
  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  
  SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
  if (!surface) {
      SDL_Log("Unable to create surface: %s", SDL_GetError());
      return 0;
  }

  if (SDL_RenderReadPixels(renderer, nullptr, surface->format->format, surface->pixels, surface->pitch) != 0) {
      SDL_Log("Unable to read pixels from renderer: %s", SDL_GetError());
      SDL_FreeSurface(surface);
      return 0;
  }

  Uint32* pixels = (Uint32*)surface->pixels;
  Uint32 pixel = pixels[(y * surface->w) + col_x];

//  SDL_FreeSurface(surface);
  return pixel;

}