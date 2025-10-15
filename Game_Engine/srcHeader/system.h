#ifndef SYSTEM_H
#define SYSTEM_H

#include  "action.h"

#include "entityManager.h"
#include "resourceManager.hpp"

#include <cmath>

// System that update the Current state of the program
// --------------------------------------------------------
class TransformSystem
{
private:
    static TransformSystem *instance;
    TransformSystem() = default;
public:
    static TransformSystem* getInstance();
    void update(float dt);
};
class RenderSystem
{
private:
    static RenderSystem *instance;
    RenderSystem()  = default;
public:
    static RenderSystem* getInstance();
    void update(float dt);

    void draw(SDL_Renderer *renderer);
};
class PhysicSystem
{
private:
    static PhysicSystem *instance;
    PhysicSystem() = default;
public:
    static PhysicSystem* getInstance();
    void update(float dt);
};
class InputSystem
{
private:
    static InputSystem *instance;
    InputSystem() = default;
public:
    static InputSystem* getInstance();
    void update();
};
// the animation system decides which part of the spritesheet/ texture will be cropped to create display
class AnimationSystem
{
private:
    static AnimationSystem *instance;
    AnimationSystem() = default;
public:
    static AnimationSystem* getInstance();
    void update(float dt);
};
// collsion is a specific system that handle collision and decide what to do if collision occur between 2 object
// we only develop the simple AABB collision between 2 object
class CollisionSystem {
    private:
    static CollisionSystem* instance;
    
    CollisionSystem(const CollisionSystem&) = delete;
    CollisionSystem() = default;
public:
    static CollisionSystem* getInstace();
    void update(float dt);
};


inline AnimationSystem* AnimationSystem::instance = nullptr;
inline TransformSystem* TransformSystem::instance = nullptr;
inline InputSystem* InputSystem::instance = nullptr;
inline RenderSystem* RenderSystem::instance = nullptr;
inline PhysicSystem* PhysicSystem::instance = nullptr;
inline CollisionSystem* CollisionSystem::instance = nullptr;
#endif