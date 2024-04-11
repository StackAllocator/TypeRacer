#include <iostream>
#include "raylib.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <filesystem>
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

void draw_text() {

}

int main() {

  constexpr int screen_width = 1280;
  constexpr int screen_height = 800;

  // Initialize the window
  // -----------------------------------------------------------------------------------
  InitWindow(screen_width, screen_height, "TypeRacer");
  SetTargetFPS(60);
  // -----------------------------------------------------------------------------------

  auto data = get_words("./resources/word_lists/english_1k.json");
  shuffle(data);

  unsigned int frame_counter = 0;

  SetTextLineSpacing(10);
  Font font = LoadFontEx("./resources/fonts/JetBrainsMono-BoldItalic.ttf", 32, 0, 250);

  Bar bar({GetScreenWidth() / 8.f, GetScreenHeight() / 5.f}, {3 * GetScreenWidth() / 4.f, GetScreenHeight() / 20.f}, 50.f, font);

  int current_seconds = 100;
  bool timer_go = false;

  float posX = 100.f;

  while (!WindowShouldClose()) {

    if (timer_go) {
      frame_counter++;
      if (frame_counter / 60 == 1) {
        current_seconds -= 1;
        frame_counter = 0;
      }
    }

    if (!timer_go && GetKeyPressed())
      timer_go = true;

    int key = GetCharPressed();

    BeginDrawing();
    // Draw the background
    ClearBackground({50, 50, 50, 255});

    DrawText("Type-Racer", GetScreenWidth() / 8, GetScreenHeight() / 12.f, 50, YELLOW);
    bar.display_bar();
    DrawTextEx(font, TextFormat("%d", current_seconds), {3 * GetScreenWidth() / 4.f, 100}, font.baseSize, 5, YELLOW);

    for (int i = 0; i < 10; ++i) {
      std::string word = std::string(data["words"][i]);
      DrawTextEx(font, word.c_str(), {posX, 300}, font.baseSize, 5, BLACK);
    }
    EndDrawing();
  }
  // De-Initialization
  UnloadFont(font);
  CloseWindow();

  return 0;
}
