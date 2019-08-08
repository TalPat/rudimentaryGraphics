#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(/* args */) {

}

Renderer::~Renderer() {

}

SDL_Window* Renderer::drawWin(int width, int height, std::string title) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize. Error: " << SDL_GetError() << std::endl;
  } else {
    return (SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL));
  }
  return (NULL);
}

void Renderer::init(State_St gameState) {
  renderer = SDL_CreateRenderer(gameState.win, -1, SDL_RENDERER_ACCELERATED);
}

void Renderer::render(State_St gameState) {
  int offset = 30;
  int unitSize = 30;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  SDL_Rect rect;
  rect.w = unitSize;
  rect.h = unitSize;

  //draw external borders
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  for (int i = 0; i < gameState.map[0] + 2; i++) {
    if (i == 0 || i == gameState.map[0] + 1) {
      for (int j = 0; j < gameState.map[1] + 2 ; j++) {
        rect.x = i * unitSize;
        rect.y = j * unitSize;
        SDL_RenderFillRect(renderer, &rect);
      }
    } else {
      rect.x = i * unitSize;
      rect.y = 0;
      SDL_RenderFillRect(renderer, &rect);
      rect.y = (gameState.map[1] + 1) * unitSize;
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  //Draw environments
  // std::cout << "env blocks: " << gameState.environments.size() <<std::endl;
  for (auto& it : gameState.environments) {
    switch (it.envType) {
      case breakable:
        SDL_SetRenderDrawColor(renderer, 102, 70, 42, 255);
      break;
      case unbreakable:
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      break;
      case levelExit:
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
      break;
      default:
      break;
    }
    rect.x = it.coord[0] * unitSize + offset;
    rect.y = it.coord[1] * unitSize + offset;
    SDL_RenderFillRect(renderer, &rect);
  }

  //Draw mobs
  for (auto& it : gameState.mobs) {
    switch (it.mobType) {
      case player:
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      break;
      case balloon:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      break;
      case robot:
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
      break;
      case bomb:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
      break;
      default:
      break;
    }
    rect.x = it.coord[0] * unitSize + (it.displacement[0] * (unitSize/2)) + offset;
    rect.y = it.coord[1] * unitSize + (it.displacement[1] * (unitSize/2)) + offset;
    SDL_RenderFillRect(renderer, &rect);
  }

  //write to screen
  SDL_RenderPresent(renderer);
}

void Renderer::closeWindow(State_St gameState) {
  std::cout << "Window Closed!" << std::endl;
  SDL_DestroyWindow(gameState.win);
  SDL_Quit();
}

int Renderer::getInput(void) {

  SDL_Event event;

  SDL_PollEvent( &event );
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
      return(0);
      break;
    case SDLK_RIGHT:
      return(1);
      break;
    case SDLK_DOWN:
      return(2);
      break;
    case SDLK_LEFT:
      return(3);
      break;
    case SDLK_ESCAPE:
      return(4);
      break;
    case ' ':
      return(5);
      break;
    default:
      return (-1);
      break;
    }
  } else if(event.type == SDL_QUIT) {
    return(4);
  } else {
    return (-1);
  }
}
