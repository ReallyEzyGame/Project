#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "gameState.h"

class GameStateManager {
public:
    static GameStateManager *getInstance();
    void pushState( std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    void update(float deltaTime);
    void handleInput(SDL_Event& event);
    void render(SDL_Window& window);  
private:
    static GameStateManager* instance;
    std::stack<std::unique_ptr<GameState>> states;

    GameStateManager() = default;
    ~GameStateManager() {delete instance; instance = nullptr;}
    GameStateManager(const GameStateManager&) = delete;
};

inline GameStateManager* GameStateManager::instance = nullptr;

#endif