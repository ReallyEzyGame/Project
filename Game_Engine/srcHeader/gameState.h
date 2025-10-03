#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class GameState
{
public:
    virtual void handleInput(SDL_Event &event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Window &window) = 0;
    virtual void onEnter() {};
    virtual void onExit() {};

    virtual ~GameState() = default;
};

class MainMenuState : public GameState
{
public:
    void handleInput(SDL_Event &event) override {}
    void update(float dt) override{}
    void render(SDL_Window &window) override  {}
    void onEnter() override {}
    void onExit() override {}

    MainMenuState() : GameState() {};
    ~MainMenuState() = default;

private:
    sf::Text menuText;
};
class SettingState : public GameState
{
public:
    void handleInput(SDL_Event &event) override;
    void update(float dt) override;
    void render(SDL_Window &window) override;
    void onEnter() override;
    void onExit() override;

    ~SettingState() = default;
};
class GamePlayState : public GameState
{
public:
    void handleInput(SDL_Event &event) override;
    void update(float dt) override;
    void render(SDL_Window &window) override;
    void onEnter() override;
    void onExit() override;

    ~GamePlayState() = default;
};
class PauseState : public GameState
{
public:
    void handleInput(SDL_Event &event) override;
    void update(float dt) override;
    void render(SDL_Window &window) override;
    void onEnter() override;
    void onExit() override;

    ~PauseState() = default;
};
#endif