#ifndef INPUTBUFFER_HPP
#define INPUTBUFFER_HPP

#include "../Compositor.hpp"
#include "../Renderer.hpp"
#include "Components/WindowComponent.hpp"
#include <sstream>

class InputBuffer : public WindowComponent
{
public:
public:
  InputBuffer(int x, int y, uint16_t cols, uint16_t rows);
  ~InputBuffer();

  void update() override;
  void render() override;

  std::string get_text();

private:
  uint16_t m_cols{1};
  uint16_t m_rows{1};
  uint16_t m_current_col{0};
  uint16_t m_current_row{0};
  uint16_t m_width{0};
  uint16_t m_height{0};

  char *buffer{nullptr};

private:
  void dec_col();
  void dec_row();
  void inc_col();
  void inc_row();
  void check_focus();
};

#endif