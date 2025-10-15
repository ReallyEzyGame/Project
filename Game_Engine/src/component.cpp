#include "component.h"

size_t TransformComponent::getID() const { return ECS::getComponentID<TransformComponent>(); }
size_t RenderComponent::getID() const { return ECS::getComponentID<RenderComponent>(); }
size_t PhysicComponent::getID() const { return ECS::getComponentID<PhysicComponent>(); }
size_t InputComponent::getID() const { return ECS::getComponentID<InputComponent>(); }
size_t AnimationComponent::getID() const { return ECS::getComponentID<AnimationComponent>(); }


TransformComponent::TransformComponent(Entity *o) : Component(o) {}
PhysicComponent::PhysicComponent(Entity *o) : Component(o)
{
    velocity = {0.f, 0.f};
    mass = 0.f;

    gravity = _GRAVITY_;
    friction = _FRICTION_;

    onGround = false;
    isGravityApplied = false;
}
RenderComponent::RenderComponent(Entity *o) : Component(o)
{
    color = {0, 0, 0, 0};
    texture_name = "";
    scale = {1.0f, 1.0f};
}
InputComponent::InputComponent(Entity *o) : Component(o) {}
AnimationComponent::AnimationComponent(Entity* o): Component(o) {timer = 0.f, frame = 0;}
// Add a new animation with the key is the name, if the name is  already exits then replace it with the new one
void AnimationComponent::addAnimation(const std::string name, Animation &anim)
{
    actions[name] = anim;
}
AnimationComponent::Animation &AnimationComponent::getAnimation(const std::string key)
{
    if (auto anim = actions.find(key); anim != actions.end())
        return anim->second;
    throw std::runtime_error("No Animation with such name was Found");
}
void AnimationComponent::play(const std::string key)
{
    if (key != current_animation)
    {
        if (auto anim = actions.find(key); anim != actions.end())
        {
            timer = 0.f;
            frame = 0;
            current_animation = key;
            animation = anim->second;
            return;
        }
        std::runtime_error("No Animation with such name was Found");
    }
}

void PhysicComponent::applyJumpForce() {
    velocity.x -= 50.f;
    onGround = false;
    isGravityApplied = true;
}


// Create a new link between keycode when press or release key on the keyboard a the action
// if the keycode already has an action, then it will be replaced
void InputComponent::addAction(SDL_KeyCode keycode, ActionType action) {
    actions[keycode] = action;
}
void InputComponent::playAction(SDL_KeyCode keycode) {
    if (auto action = actions.find(keycode); action != actions.end()) {
        current_action = action->second;
    }
}
void InputComponent::eraseAction(SDL_KeyCode keycode) {
    actions.erase(keycode);
}