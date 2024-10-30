#ifndef WINDOWCOMPONENT_HPP
#define WINDOWCOMPONENT_HPP

#include "../Component.hpp"

class WindowComponent : public Component
{
public:
  virtual void set_position(const int x, const int y)
  {
    m_x = x;
    m_y = y;
  }
  virtual int get_x()
  {
    return m_x;
  };
  virtual int get_y()
  {
    return m_y;
  };

  virtual bool is_primary()
  {
    return m_is_primary;
  }

  virtual void add_event(void *func) {}

  virtual void enable()
  {
    m_enabled = true;
  }

  virtual void disable()
  {
    m_enabled = false;
  }

  virtual void set_visible(bool vis)
  {
    m_visible = vis;
    if (!vis)
    {
      m_is_primary = false;
    }
  }

protected:
  bool m_enabled{true};
  bool m_visible{true};
  bool m_is_primary{true};
};

#endif