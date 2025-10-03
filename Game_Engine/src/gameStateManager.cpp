#include "gameStateManager.h"

GameStateManager *GameStateManager::getInstance()
{
    if (instance == nullptr) {
        instance = new GameStateManager();
    }
    return instance;
}
void GameStateManager::pushState(std::unique_ptr<GameState> state)
{
    if (state == nullptr)
        return;

    if (!states.empty())
        states.top()->onExit();
    states.push(move(state));
    states.top()->onEnter();
}
void GameStateManager::popState()
{
    if (!states.empty())
    {
        states.top()->onExit();
        states.pop();
    }
    if (!states.empty())
        states.top()->onEnter();
}
void GameStateManager::changeState(std::unique_ptr<GameState> state)
{
    if (state != nullptr)
    {
        if (!states.empty())
        {
            states.top()->onExit();
            states.pop();
        }
        states.push(std::move(state));
        states.top()->onEnter();
    }
}
void GameStateManager::update(float deltaTime)
{
    if (!states.empty())
    {
        states.top()->update(deltaTime);
    }
}
void GameStateManager::handleInput(SDL_Event& event)    
{
    if (!states.empty())
    {
        states.top()->handleInput(event);
    }
}
void GameStateManager::render(SDL_Window &window)
{
    if (!states.empty())
    {
        states.top()->render(window);
    }
}