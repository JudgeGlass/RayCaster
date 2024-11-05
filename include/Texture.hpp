#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Texture
{
public:
  Texture(std::string filename, int pw, int ph);
  void load(SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer, int tile, int x, int y, int scale, int rowa);
  int get_pixel(SDL_Renderer *renderer, int tile, int col_x, int y, int rowa);
  int pw;
  int ph;
  std::string filename;
  SDL_Texture *texture;

private:
};

#endif