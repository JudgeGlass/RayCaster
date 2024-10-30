#ifndef CHICAGOSDL_TYPES_H
#define CHICAGOSDL_TYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <functional>
#include <inttypes.h>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <stack>
#include <string>
#include <vector>

#include "Compositor.hpp"
#include "Renderer.hpp"
#include "Singleton.hpp"
#include "Texture.hpp"
#include "Window.hpp"
#include "WindowMgr.hpp"

#include "Components/Button.hpp"
#include "Components/CheckBox.hpp"
#include "Components/InputBuffer.hpp"
#include "Components/Label.hpp"
#include "Components/WindowComponent.hpp"

class Compositor;
class Renderer;
class Texture;
class Window;
class WindowMgr;

class Button;
class CheckBox;
class InputBuffer;
class Label;
class WindowComponent;

#endif