#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include "WindowMgr.hpp"
#include "Renderer.hpp"

class Game {
  public:
    Game();

    void update();
    void render();

    void draw_rect(const int x, const int y, const int w, const int h);

  private:
    const int MAP_WIDTH = 12;
    const int MAP_HEIGHT = 24;
};

#endif