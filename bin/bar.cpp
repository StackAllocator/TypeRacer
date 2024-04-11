#include "raylib.h"
#include "bar.hpp"

Bar::Bar(Vector2 position, Vector2 size, float box_width, Font font)
      : m_position(position), m_size(size), m_font(font) {
    this->time_boxes.push_back(std::pair<std::string, Rectangle>("30", {position.x + size.x - box_width * 4, position.y, box_width, 40}));
    this->time_boxes.push_back(std::pair<std::string, Rectangle>("60", {position.x + size.x - box_width * 3, position.y, box_width, 40}));
    this->time_boxes.push_back(std::pair<std::string, Rectangle>("120", {position.x + size.x - box_width * 2, position.y, box_width, 40}));
  }

void Bar::display_bar() {
  DrawRectangleRounded({
      m_position.x,
      m_position.y,
      m_size.x,
      m_size.y

  },0.5f, 0.f, {30, 30, 30, 100});

  for (auto &[seconds, rect] : time_boxes) {
    Vector2 mouse_pos = GetMousePosition();

    if (mouse_pos.x >= rect.x && mouse_pos.x <= rect.x + rect.width && mouse_pos.y >= rect.y && mouse_pos.y <= rect.y + rect.height) {
      text_color = YELLOW;

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

      }
    }
    else {
      text_color = RAYWHITE;
    }
    DrawTextEx(m_font, seconds.c_str(), {rect.x + 10, rect.y + 10}, 20, 2, text_color);
  }
  DrawRectangleRounded({m_position.x + m_size.x - 50 * 5, m_position.y, 10, 40}, 0.5, 0.f, {50, 50, 50, 250});
}
