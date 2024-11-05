#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <sstream>

#include "WindowMgr.hpp"

class WindowMgr;
class ViewPort{
public:
  ViewPort(const Game* game);

  void update();
  void render();


public:

private:
  void debug();

private: 
  const Game *m_game_ptr;
  WindowMgr *window_manager;

  //Button *m_close_btn;
};

#endif