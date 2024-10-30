#include "Components/InputBuffer.hpp"

InputBuffer::InputBuffer(int x, int y, uint16_t cols, uint16_t rows) : m_cols(cols), m_rows(rows)
{
  m_x = x;
  m_y = y;

  buffer = new char[cols * rows];

  m_width = (cols * 8) + 10;
  m_height = (rows * 8) + 10;

  for (int i = 0; i < cols * rows; i++)
  {
    buffer[i] = ' ';
  }
}

InputBuffer::~InputBuffer()
{
  delete[] buffer;
}

void InputBuffer::update()
{
  check_focus();
  if (!m_is_primary)
  {
    return;
  }
  std::string key = WindowMgr::get_instance().get_text_input();
  bool backspace = WindowMgr::get_instance().backspace_pressed();
  bool up = WindowMgr::get_instance().is_key_pressed(SDLK_UP);
  bool down = WindowMgr::get_instance().is_key_pressed(SDLK_DOWN);
  bool left = WindowMgr::get_instance().is_key_pressed(SDLK_LEFT);
  bool right = WindowMgr::get_instance().is_key_pressed(SDLK_RIGHT);
  if (!key.empty())
  {
    buffer[m_current_col + m_current_row * m_cols] = key.at(0);
    if (m_current_col + 1 > m_cols - 1)
    {
      m_current_col = 0;
      if (m_current_row + 1 < m_rows - 1)
      {
        m_current_row++;
      }
    }
    else
    {
      m_current_col++;
    }
  }

  if (backspace)
  {
    if (m_current_col - 1 < 0)
    {
      m_current_col = m_cols - 1;
      if (m_current_row - 1 >= 0)
      {
        m_current_row--;
      }
    }
    else
    {
      m_current_col--;
    }
    buffer[m_current_col + m_current_row * m_cols] = ' ';
  }

  if (up)
  {
    dec_row();
  }
  if (left)
  {
    dec_col();
  }
  if (right)
  {
    inc_col();
  }
  if (down)
  {
    inc_row();
  }
}

void InputBuffer::render()
{
  Renderer *renderer = WindowMgr::get_instance().get_renderer();

  // renderer->render_color(0xFF, 0xFF, 0xFF);
  // renderer->render_rect(m_x, m_y, m_width, m_height, true);
  Compositor::get_instance().draw_input_buffer(m_x, m_y, m_cols, m_rows, buffer);

  for (int c = 0; c < m_cols; c++)
  {
    for (int r = 0; r < m_rows; r++)
    {
      int x = c * 8 + 5 + m_x;
      int y = r * 8 + 5 + m_y + 2;
      renderer->draw_string(x, y, std::string(1, buffer[c + r * m_cols]), 0, 1);
    }
  }

  renderer->render_color(0, 0, 0);
  renderer->render_rect(m_current_col * 8 + m_x + 5, m_current_row * 8 + m_y - 2 + 16, 8, 2, true);
}

void InputBuffer::dec_col()
{
  if (m_current_col - 1 < 0)
  {
    m_current_col = m_cols - 1;
  }
  else
  {
    m_current_col--;
  }
}

void InputBuffer::dec_row()
{
  if (m_current_row - 1 < 0)
  {
    m_current_row = m_rows - 1;
  }
  else
  {
    m_current_row--;
  }
}

void InputBuffer::inc_col()
{
  if (m_current_col + 1 > m_cols - 1)
  {
    m_current_col = 0;
  }
  else
  {
    m_current_col++;
  }
}

void InputBuffer::inc_row()
{
  if (m_current_row + 1 > m_rows - 1)
  {
    m_current_row = 0;
  }
  else
  {
    m_current_row++;
  }
}

std::string InputBuffer::get_text()
{
  std::stringstream ss;
  for (int c = 0; c < m_cols; c++)
  {
    for (int r = 0; r < m_rows; r++)
    {
      ss << buffer[c + r * m_cols];
    }
    ss << "\n";
  }

  return ss.str();
}

void InputBuffer::check_focus()
{
  int mouse_x = WindowMgr::get_instance().get_mouse_pos().first;
  int mouse_y = WindowMgr::get_instance().get_mouse_pos().second;
  if (WindowMgr::get_instance().m_mouse1_pressed &&
      Component::is_in_bounds(mouse_x, mouse_y, m_x, m_y, m_width, m_height))
  {
    m_is_primary = true;
  }
  if (WindowMgr::get_instance().m_mouse1_pressed &&
      !Component::is_in_bounds(mouse_x, mouse_y, m_x, m_y, m_width, m_height))
  {
    m_is_primary = false;
  }
}