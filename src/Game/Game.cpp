#include "Game/Game.hpp"
#include <iostream>
#include <cmath>

#define VIEW_START_X (12*32)
#define VIEW_START_Y 5
#define VIEW_END_X (4 * 240)
#define VIEW_END_Y (4 * 128)
#define VIEW_VERT_CENTER (VIEW_START_Y + (VIEW_END_Y / 2))
#define VIEW_WIDTH (VIEW_END_X - VIEW_START_X)
#define VIEW_HEIGHT (VIEW_END_Y - VIEW_START_Y)

static constexpr char m_map[12*24] = 
    {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1,
      1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 2, 3, 0, 1, 0, 1,
      1, 1, 1, 0, 0, 0, 3, 3, 3, 3, 2, 1,
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


Game::Game(){
  m_player = std::make_shared<Player>(this);
  m_viewport = std::make_shared<ViewPort>(this);
}

void Game::update(){
  m_viewport->update();
  bool up = WindowMgr::get_instance().is_key_pressed(SDLK_UP);
  bool down = WindowMgr::get_instance().is_key_pressed(SDLK_DOWN);
  bool left = WindowMgr::get_instance().is_key_pressed(SDLK_LEFT);
  bool right = WindowMgr::get_instance().is_key_pressed(SDLK_RIGHT);

  if(up) m_py_offset--;
  if(down) m_py_offset++;
  if(left) m_px_offset--;
  if(right) m_px_offset++;
}

void Game::render(){
  m_viewport->render();
  Renderer* r = WindowMgr::get_instance().get_renderer();


  for(int x = 0; x < MAP_WIDTH; x++)
  {
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
      if(m_map[x + y * MAP_WIDTH] == 0) continue;
      int color = m_map[x + y * MAP_WIDTH];
      if(color == 1)
        r->render_color(0xFF, 0x0, 0x0);
      else if(color == 2)
        r->render_color(0x00, 0xFF, 0x0);
      else if(color == 3)
        r->render_color(0x00, 0x00, 0xFF);
      r->render_rect(x * 32, y * 32, 32, 32, true);
    }
  }

  int x1 = 32 + m_px_offset;
  int y1 = 32 + m_py_offset;
  int mx = WindowMgr::get_instance().get_mouse_pos().first;
  int my = WindowMgr::get_instance().get_mouse_pos().second;

  int mouse_dx = (mx - x1);
  int mouse_dy = (my - y1);


  int angle = (int)(( atan( ((double)(my - y1) / (double)(mx - x1)) )) * 180/3.14);
  if(mouse_dx < 0) angle += 180;

  const int MAX_RAY_LEN = 32 * 30;
  const float step = 0.1f;
  double x = x1, y = y1;

  double ab = angle;
  double a = ab - 30.0;
  int ray_count = 0;
  int color = 0;
  int bx = 0;
  for(; a <= ab + 30.0; a+=0.25, ray_count++) // 60 deg / 240 rays = 0.25deg/ray
  {
    float dy = step * sin((double)a * 3.145 / 180.0);
    float dx = step * cos((double)a * 3.145 / 180.0);
    x = 32 + m_px_offset;
    y = 32 + m_py_offset;
    for(float i = 0.0f; i < MAX_RAY_LEN; i += step)
    {
      x += dx;
      y += dy;

      int xx = (int) x - ((int) x % 32);
      int yy = (int) y - ((int) y % 32);
      
      if((x > xx && x < xx + 32 && y > yy && y < yy + 32) && m_map[(xx / 32) + (yy / 32) * MAP_WIDTH] != 0)
      {
        color = m_map[(xx / 32) + (yy / 32) * MAP_WIDTH];
        bx = (int)x % 32;
        break;
      }
    }
    
    r->render_color(0xFF, 0xFF, 0x00);
    r->draw_line(x1, y1, (int)x, (int)y);

    double ddy = y - y1;
    double ddx = x - x1;
    double m = dy/dx;
    std::cout << bx << std::endl;
    Face f = WEST;

    double d = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y)) * abs(cos((double) a * 3.145 / 180.0));
    draw_view_line(ray_count, 1.0 - (d / MAX_RAY_LEN), color, f);

    r->draw_line(VIEW_START_X, VIEW_START_Y, VIEW_START_X + VIEW_END_X, VIEW_START_Y);
    r->draw_line(VIEW_START_X, VIEW_START_Y + (VIEW_END_Y / 2), VIEW_START_X + VIEW_END_X, VIEW_START_Y + (VIEW_END_Y / 2));
    r->draw_line(VIEW_START_X, VIEW_START_Y + VIEW_END_Y, VIEW_START_X + VIEW_END_X, VIEW_START_Y + VIEW_END_Y);
  }
}

void Game::draw_view_line(int pos, double percent, int color, int texture_col){
  Renderer* renderer = WindowMgr::get_instance().get_renderer();
  int x = pos * 4 + VIEW_START_X;
  int y = VIEW_START_Y;
  int line_height = (int) (percent * VIEW_HEIGHT);

  int sy = VIEW_VERT_CENTER - (line_height / 2);
  int ey = VIEW_VERT_CENTER + (line_height / 2);

  //std::cout << "sy: " << sy << "\tey: " << ey << std::endl;

  int r = 0xFF;
  int g = 0xFF;
  int b = 0xFF;



  if(color == 1){
    g = 0;
    b = 0;
    r -= texture_col * 10;
  }
  else if(color == 2){
    r = 0;
    b = 0;
    g -= texture_col * 10;
  }
  else if(color == 3){
    r = 0;
    g = 0;
    b -= texture_col * 10;
  }

  renderer->render_color(r, g, b);

  for(int i = 1; i <= 4; i++)
    renderer->draw_line(x + i, sy, x + i, ey);
}