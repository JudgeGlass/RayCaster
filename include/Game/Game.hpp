#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include "WindowMgr.hpp"
#include "Renderer.hpp"

#include "Game/Player.hpp"
#include "Game/Viewport.hpp"

enum Face {
  NORTH,
  SOUTH,
  EAST,
  WEST
};

class ViewPort;
class Game {
  public:
    Game();

    void update();
    void render();

    void draw_rect(const int x, const int y, const int w, const int h);

    void draw_view_line(int pos, double percent, int color, int texture_col);

  private:
    const int MAP_WIDTH = 12;
    const int MAP_HEIGHT = 24;

    int m_px_offset = 0;
    int m_py_offset = 0;

    std::shared_ptr<Player> m_player;
    std::shared_ptr<ViewPort> m_viewport;
};

#endif