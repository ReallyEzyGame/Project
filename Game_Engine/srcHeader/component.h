#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"
#include "imgui.h"


#define _GRAVITY_ 9.80655
#define _FRICTION_ 0.95

class Entity;
class Component;
class Texture;

enum class ActionType;

namespace ECS
{
    inline size_t nextID_component = 0;
    template <typename T>
    size_t getComponentID()
    {
        static size_t id = nextID_component++;
        return id;
    }
};

// Component class the hold the information of each component
// -------------------------------------------------------------
class Component
{
protected:
    Entity *owner = nullptr;

public:
    Component(Entity *o) : owner(o) {}
    virtual ~Component() = default;
    
    virtual size_t getID() const = 0;
    virtual std::string getName() const = 0;
};



class TransformComponent : public Component
{
public:
    TransformComponent(Entity *);
    size_t getID() const override;
    std::string getName() const override { return "Transform"; }

    ImVec2 position;
    float rotation;
};
class RenderComponent : public Component
{
public:
    RenderComponent(Entity *);
    ~RenderComponent() = default;

    size_t getID() const override;
    std::string getName() const override { return "Render"; }

    std::string texture_name;
    ImVec2 scale, size;
    ImColor color;

    ImVec4 crop; // this data only for system using
};
class PhysicComponent : public Component
{
public:
    PhysicComponent(Entity *);

    size_t getID() const override;
    std::string getName() const override { return "Physic"; }
    void applyJumpForce();

    ImVec2 velocity;
    float mass;

    float gravity;
    float friction;

    bool onGround;
    bool isGravityApplied;
};
class InputComponent : public Component
{
public:
    std::unordered_map<SDL_KeyCode, ActionType> actions;
    ActionType current_action;

    InputComponent(Entity *o);

    std::string getName() const override { return "Input"; }
    size_t getID() const override;


    void addAction(SDL_KeyCode, ActionType);
    void playAction(SDL_KeyCode);
    void eraseAction(SDL_KeyCode);
};
class AnimationComponent : public Component
{
public:
    struct Animation
    {
        std::vector<ImVec4> frames;
        float frame_time;
    };

    std::unordered_map<std::string, Animation> actions;

    float timer;
    unsigned int frame;
    std::string current_animation;
    Animation animation;

    AnimationComponent(Entity *);

    std::string getName() const override { return "Animation"; }
    size_t getID() const override;

    // Add a new animation with the key is the name, if the name is  already exits then replace it with the new one
    void addAnimation(const std::string name, Animation &anim);
    Animation &getAnimation(const std::string key);
    void play(const std::string key);
};

class RigidBodyComponent : public Component
{
public:
};
// Contains information about the AABB collision for each entity
class CollisionComponent : public Component
{
public:
    SDL_FRect *collision_box = nullptr; // Handle AABB Collision
    ImVec4 size;
    ImVec2 offset; // position of  the top-left corner compare to object's center
    bool IsTrigger;
    std::string material; // Material made from the object, for interaction with the enviroment
};

#endif