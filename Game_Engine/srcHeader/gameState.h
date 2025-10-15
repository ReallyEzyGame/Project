#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>
#include <iostream>

#include "imgui.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class GameState
{
private:
    size_t id;
    std::string name;
public:
    virtual void handleInput(SDL_Event &event);
    virtual void update(float deltaTime);
    
    virtual void render(SDL_Window &window);

    virtual void onEnter();
    virtual void onExit();

    virtual ~GameState() = default;
};


#endif