#ifndef WINDOWMGR_HPP
#define WINDOWMGR_HPP

#include <SDL2/SDL.h>
#include <inttypes.h>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "Component.hpp"
#include "Renderer.hpp"
#include "Singleton.hpp"
#include "Game/Game.hpp"

class Component;
class Game;
class WindowMgr : public Singleton<WindowMgr>
{
  friend class Singleton<WindowMgr>;

public:
  bool m_mouse1_pressed{false};
  float fps = 0.0f;
  uint16_t m_window_width{800};
  uint16_t m_window_height{480};

public:
  ~WindowMgr();

  void init(const uint16_t window_width, const uint16_t window_height, const std::string &window_title, std::shared_ptr<Game> game);
  void loop();
  void log(const std::string &msg, bool _exit);
  void close();
  void add_component(Component *component);
  void remove_component(Component *component);
  void set_focus(Component *component);
  void toggle_border();
  void set_all_key_states(bool value);

  char pop_key_buffer();
  bool backspace_pressed();
  bool is_key_pressed(SDL_Keycode key);

  Renderer *get_renderer();

  std::string get_text_input();

  std::pair<int, int> get_mouse_pos();

private:
  std::string m_window_title;
  std::string m_text_input;

  bool m_loop{false};
  bool m_show_border{false};
  bool m_char_removed{false};

  int m_mouse_x{0};
  int m_mouse_y{0};

  SDL_Window *m_sdl_window;
  SDL_Renderer *m_sdl_renderer;

  std::unique_ptr<Renderer> m_renderer;

  std::vector<Component *> m_components;
  std::vector<char> m_key_buffer;

  std::stack<Component *> m_current_focus;

  std::map<SDL_Keycode, bool> m_key_states;

  std::shared_ptr<Game> m_game;

private:
  void sdl_init();
  void sdl_event();
  void render();
  void update();
};

#endif