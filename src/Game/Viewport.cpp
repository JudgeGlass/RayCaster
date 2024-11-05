#include "Game/Viewport.hpp"

ViewPort::ViewPort(const Game* game)
: m_game_ptr(game){
  window_manager = &WindowMgr::get_instance();

  
}

void ViewPort::update(){

}

void ViewPort::render(){

  
  debug(); // Draw last
}

void ViewPort::debug(){
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  int start_x = window_manager->m_window_width - 128;
  int start_y = 5;

  int mouse_x = window_manager->get_mouse_pos().first;
  int mouse_y = window_manager->get_mouse_pos().second;

  std::stringstream ss;
  ss << "RayCaster v0.0.1\n";
  ss << "MX: " << mouse_x << " MY: " << mouse_y << "\n";

  renderer->draw_string(start_x, start_y, ss.str(), 0xFFFFFF, 1);
}