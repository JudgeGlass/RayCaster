cmake_minimum_required(VERSION 3.16)
project(RayCaster)


set(CMAKE_CXX_STANDARD 17)

include_directories("include")

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -ggdb")
LINK_LIBRARIES(SDL2main SDL2 SDL2_image SDL2_mixer)
add_executable(RayCaster
    src/main.cpp
    src/WindowMgr.cpp
    src/Renderer.cpp
    src/Window.cpp
    src/Texture.cpp
    src/Compositor.cpp

    src/Components/Button.cpp
    src/Components/CheckBox.cpp
    src/Components/Label.cpp
    src/Components/InputBuffer.cpp
    src/Components/Graphics.cpp

    src/Game/Game.cpp
    src/Game/Player.cpp
    src/Game/Viewport.cpp
    src/Game/Level.cpp
)
