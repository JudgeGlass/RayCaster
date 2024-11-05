#include "Game/Player.hpp"

Player::Player(Game* game){
  this->m_game_ptr = game;
}

int Player::get_x() const {
  return m_x;
}

int Player::get_y() const{
  return m_y;
}