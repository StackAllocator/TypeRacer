#pragma once

#include "raylib.h"
#include <vector>
#include <string>

enum class Selected_Time {
  THIRTY_SEC,
  ONE_MIN,
  TWO_MIN,
};

class Bar {
  public:

  Bar(Vector2 position, Vector2 size, float box_width, Font font);
  void display_bar();

  private:
    std::vector<std::pair<std::string, Rectangle>> time_boxes;
    Font m_font;

    Color text_color = RAYWHITE;
    Selected_Time current_time = Selected_Time::THIRTY_SEC;

    Vector2 m_position;
    Vector2 m_size;
};
