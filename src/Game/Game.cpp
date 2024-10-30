#include "Game/Game.hpp"
#include <iostream>
#include <cmath>

static constexpr char m_map[12*24] = 
    {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1,
      1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1,
      1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1,
      1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1
    };


Game::Game(){}

void Game::update(){

}

void Game::render(){
  Renderer* r = WindowMgr::get_instance().get_renderer();


  for(int x = 0; x < MAP_WIDTH; x++)
  {
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
      if(m_map[x + y * MAP_WIDTH] == 0) continue;
      r->render_color(0xFF, 0xFF, 0xFF);
      r->render_rect(x * 32, y * 32, 32, 32, true);
    }
  }

  int x1 = 32 * 4;
  int y1 = 32 * 7;
  int mx = WindowMgr::get_instance().get_mouse_pos().first;
  int my = WindowMgr::get_instance().get_mouse_pos().second;

  int mouse_dx = (mx - x1);
  int mouse_dy = (my - y1);


  int angle = (int)(( atan( ((double)(my - y1) / (double)(mx - x1)) )) * 180/3.14);
  if(mouse_dx < 0) angle += 180;

  const int MAX_RAY_LEN = 32 * 30;
  const float step = 0.01f;
  double x = x1, y = y1;

  int ab = angle;
  for(int a = ab - 30; a <= ab + 30; a++)
  {
    float dy = step * sin((double)a * 3.145 / 180.0);
    float dx = step * cos((double)a * 3.145 / 180.0);
    x = 32 * 4;
    y = 32 * 7;
    for(float i = 0.0f; i < MAX_RAY_LEN; i += step)
    {
      x += dx;
      y += dy;

      int xx = (int) x - ((int) x % 32);
      int yy = (int) y - ((int) y % 32);
      
      if((x > xx && x < xx + 32 && y > yy && y < yy + 32) && m_map[(xx / 32) + (yy / 32) * MAP_WIDTH] == 1)
      {
        break;
      }
    }
    
    r->render_color(0xFF, 0xFF, 0x00);
    r->draw_line(x1, y1, (int)x, (int)y);
  }
}