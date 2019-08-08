#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SDL2/SDL.h>
#include <string>
#include "GameState.hpp"

class Renderer
{
private:
  SDL_Renderer * renderer;
public:
  Renderer(/* args */);
  ~Renderer();
  SDL_Window* drawWin(int width, int height, std::string title);
  void init(State_St gameState);
  void render(State_St gameState);
  void closeWindow(State_St gameState);
  int getInput(void);
};


#endif