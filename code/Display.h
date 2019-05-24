#pragma once
#include <string>
#include <SDL2/SDL.h>

class Display {
public:
  Display(int width, int height, const std::string& title);
  virtual ~Display();

  void clear(float r, float g, float b, float a);
  void update();
  bool is_closed();

private:
  SDL_Window* window_;
  SDL_GLContext gl_context_;
  bool is_closed_;
};
