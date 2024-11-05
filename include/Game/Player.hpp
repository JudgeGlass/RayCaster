#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

class Game;
class Player{
public:
  Player(Game* game);
public:

private:
  int get_x() const;
  int get_y() const;

private:
  Game* m_game_ptr;

  int m_x;
  int m_y;
};

#endif