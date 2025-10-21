#include "system.h"



// Check for Collision between 2 object
//
void AABB_CollisionHandle(Entity* e1, Entity* e2, const float  dt) {
    if (!e1 || !e2) return;

    auto coll1 = e1->getComponent<CollisionComponent>();
    auto phys1 = e1->getComponent<PhysicComponent>();
    auto tran1 = e1->getComponent<TransformComponent>();

    auto coll2 = e2->getComponent<CollisionComponent>();
    auto phys2 = e2->getComponent<PhysicComponent>();
    auto tran2 = e2->getComponent<TransformComponent>();


    if (!coll1 ||  !coll2) return;                          // Entity doesn't have Collision Box
    if (!phys1 || !phys2) return;
    if (!coll1->IsTrigger || !coll2->IsTrigger) return;     // Collision doesn't affect


    // Continuous Collision Detection
    // Swept AABB Collision

    // Position posibly on x-axis in the furture
    SDL_FRect* new_1 = coll1->collision_box;
    SDL_FRect* new_2 = coll2->collision_box;

    new_1->x = new_1->x + phys1->velocity.x * dt;
    new_2->x =  new_2->x + phys2->velocity.x * dt;

    // check for Collision on horizontal
    SDL_FRect* collision_rect;
    if(SDL_IntersectFRect(new_1, new_2, collision_rect)) {
        // handling AABB collision on Horizontal

        // collsion occurss on the right side
        if (new_1->x >= new_2->x && new_1->x <= new_2->x + new_2->w) {
            phys1->velocity.x = 0;

            tran1->position.x -= 0.01f;
        }
        // collision occurs on the left side
        else {
            phys1->velocity.x = 0;

            tran1->position.x += 0.01f;
        }
    }
    

    // Position posibly on y-axis in the furture
    new_1 = coll1->collision_box;
    new_2 = coll2->collision_box;

    new_1->y = new_1->y + phys1->velocity.y * dt;
    new_2->y = new_2->y + phys2->velocity.y * dt;

    if(SDL_IntersectFRect(new_1, new_2, collision_rect)) {
        // handling AABB collision on Vertical
        // Ceiling collsion
        if (new_1->y <= new_2->y && new_1->y >= new_2->y + new_2->h) {
            phys1->velocity.y = 0;

            tran1->position.y -= 0.01f;
        }
        else {
            phys1->velocity.y = 0;

            phys1->onGround = true;
            phys1->isGravityApplied = false;

            tran1->position.y += 0.01f;
        }
    }
}



void TransformSystem::update(float dt)
{
    auto entity_manager = EntityManager::getInstance();
    for (std::unique_ptr<Entity> &e : entity_manager->entities)
    {
        auto trans = e->getComponent<TransformComponent>();
        auto phys = e->getComponent<PhysicComponent>();

        if (trans && phys)
        {
            trans->position.x += phys->velocity.x * dt;
            trans->position.y += phys->velocity.y * dt;
        }
    }
}
void PhysicSystem::update(float dt)
{
    auto entity_manager = EntityManager::getInstance();
    size_t n = entity_manager->entities.size();
    for (size_t i = 0; i < n; ++i)
    {
        std::unique_ptr<Entity> &e1 = entity_manager->entities[i];
        auto render1 = e1->getComponent<RenderComponent>();
        auto phys1 = e1->getComponent<PhysicComponent>();
        auto tran1 = e1->getComponent<TransformComponent>();

        if (!render1 || !phys1 || !tran1)
            continue;

        phys1->velocity.x -= phys1->friction * dt;
        phys1->velocity.y += phys1->gravity * dt;

        for (size_t j = i + 1; j < n; ++j)
        {
            std::unique_ptr<Entity> &e2 = entity_manager->entities[j];
            auto phys2 = e2->getComponent<PhysicComponent>();
            auto tran2 = e2->getComponent<TransformComponent>();

            if (!phys2 || !tran2)
                continue;

            tran1->position.x += phys1->velocity.x * dt;
            tran1->position.y += phys1->velocity.y * dt;
        }
    }
}
void InputSystem::update() {
    auto entity_manager = EntityManager::getInstance();

    for (auto& e : entity_manager->entities) {
        auto input = e->getComponent<InputComponent>();
        
        if (input) {
            // Hanlde Input Event
        }
    }
}
void RenderSystem::update(float dt)
{
    auto entity_manager = EntityManager::getInstance();
    for (auto &e : entity_manager->entities)
    {
        auto rend = e->getComponent<RenderComponent>();
        auto anim = e->getComponent<AnimationComponent>();

        if (!rend || !anim)
            continue;

        anim->timer += dt;

        if (anim->timer > anim->animation.frame_time)
        {
            anim->timer = 0.f;
            if (anim->animation.frames.size())
                anim->frame = (anim->frame + 1) % anim->animation.frames.size();
        }
        if (!anim->animation.frames.empty())
            rend->crop = anim->animation.frames[anim->frame];
    }
}
void AnimationSystem::update(float dt)
{
    auto entity_manager = EntityManager::getInstance();
    for (std::unique_ptr<Entity> &e : entity_manager->entities)
    {
        auto rend = e->getComponent<RenderComponent>();
        auto anim = e->getComponent<AnimationComponent>();

        if (rend && anim)
        {
            anim->timer += dt;
            if (anim->timer > anim->animation.frame_time)
            {
                anim->timer = 0;
                if (!anim->animation.frames.empty())
                    anim->frame = (anim->frame + 1) % anim->animation.frames.size();
            }
            // update a part of the Texure
        }
    }
}
void CollisionSystem::update(float dt) {
    auto entity_manager = EntityManager::getInstance();

    for (auto& e1 : entity_manager->entities) {
        for (auto& e2 : entity_manager->entities) {
            AABB_CollisionHandle(e1.get(),e2.get(),dt);
        }
    }
}




TransformSystem *TransformSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TransformSystem();
    }
    return instance;
}
PhysicSystem *PhysicSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new PhysicSystem();
    }
    return instance;
}
InputSystem *InputSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new InputSystem();
    }
    return instance;
}
RenderSystem *RenderSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new RenderSystem();
    }
    return instance;
}
AnimationSystem *AnimationSystem::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AnimationSystem();
    }
    return instance;
}
CollisionSystem* CollisionSystem::getInstace() {
    if (instance ==  nullptr) {
        instance = new CollisionSystem();
    }
    return instance;
}
