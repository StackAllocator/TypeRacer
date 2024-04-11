#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>

#include "raylib.h"
#include "bar.hpp"
#include "json.hpp"


using json = nlohmann::json;

// retrieve json word_list data
json get_words(std::string file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + file_path);
  }

  json data = json::parse(file);
  file.close();
  return data;
}

void shuffle(json &data) {
  // Initialize mersenne twister engine.
  std::mt19937 mt(std::random_device{}());

  // shuffle the words in the word list
  std::shuffle(data["words"].begin(), data["words"].end(), mt);
}


int main() {

  constexpr int screen_width = 1280;
  constexpr int screen_height = 800;

  // Initialize the window
  // -----------------------------------------------------------------------------------------------------------------------------
  InitWindow(screen_width, screen_height, "TypeRacer");
  SetTargetFPS(60);
  // -----------------------------------------------------------------------------------------------------------------------------

  // Get word-list data
  auto data = get_words("./resources/word_lists/english_1k.json");
  shuffle(data);

  unsigned int frame_counter = 0;

  // SetTextLineSpacing(10);
  Font font = LoadFontEx("./resources/fonts/JetBrainsMono-BoldItalic.ttf", 32, 0, 250);

  Bar bar({GetScreenWidth() / 8.f, GetScreenHeight() / 5.f}, {3 * GetScreenWidth() / 4.f, GetScreenHeight() / 20.f}, 50.f, font);
  int current_seconds = 30;

  Vector2 text_position = {150, 300};
  float horizontal_spacing = 0;
  float vertical_spacing = 0;

  // -----------------------------------------------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) {

    BeginDrawing();
    // Draw the background
    ClearBackground({50, 50, 50, 255});

    DrawText("Type-Racer", GetScreenWidth() / 8, GetScreenHeight() / 12.f, 50, YELLOW);
    bar.display_bar();
    DrawTextEx(font, TextFormat("%d", current_seconds), {1 / 8.f * GetScreenWidth(), 250}, font.baseSize, 5, YELLOW);

    for (int i = 0; i < 100; ++i) {
      DrawText(std::string(data["words"][i]).c_str(), text_position.x + i * 100, text_position.y + i * vertical_spacing, 30, BLACK);
    }

    EndDrawing();
  }
  // -----------------------------------------------------------------------------------------------------------------------------
  // De-Initialization
  UnloadFont(font);
  CloseWindow();

  return 0;
}
