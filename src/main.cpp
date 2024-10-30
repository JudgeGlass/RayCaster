#include "Components/Button.hpp"
#include "Components/CheckBox.hpp"
#include "Components/Graphics.hpp"
#include "Components/InputBuffer.hpp"
#include "Components/Label.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"
#include <SDL2/SDL.h>
#include <iostream>

#define SDL_MAIN_HANDLED

void build_window()
{
  std::shared_ptr<Game> game = std::make_shared<Game>();

  WindowMgr *window_manager = &WindowMgr::get_instance();
  WindowMgr::get_instance().init(800 * 2, 480 * 2, "ChicagoSDL", game);



  WindowMgr::get_instance().loop();
}

int main()
{
  build_window();
  std::cout << "(ChicagoSDL exit)" << std::endl;
  return 0;
}