#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include <algorithm>
#include <string>
#include <queue>
#include <map>

const float _EARTH_GRAVITY = 9.80665;

using namespace std;
using namespace sf;

class Entity;
class Game;
class TileMap;

enum class EntityType
{
    Player,
    Enemy,
    Wall,
    Ground,
    Collectible
};
enum class StateType
{
    Standing,
    Walking,
    Sprinting,
    Climbing
};

int toInteger(const string digits);
float toFloat(const string digits);
vector<string> readFromFile(const string);
vector<vector<string>> readExcludeSpace(const string filePath, const int argc);

// A Virtual class of components require for each entity/ object in the Game
class Component
{
public:
    Entity *owner = nullptr;
    Component(Entity *o) : owner(o) {}
    virtual ~Component() = default;
    virtual void init() {};
    virtual void draw(RenderWindow &window) {};
    virtual void update(float deltaTime) {};
};

// Contain the current state of Entity include: position, size, rotation
class TransformComponent : public Component
{
public:
    Vector2f position{0.f, 0.f};
    Vector2f size{32, 32};
    float rotation{0.f};

    TransformComponent(Entity *o, const Vector2f _pos = {0, 0}, const Vector2f sz = {32, 32}, const float rota = 0.f) : Component(o), position(_pos), size(sz), rotation(rota) {}
};

// a Component that Handling drawing enity/ object on the window
class RenderComponent : public Component
{
public:
    Texture texture;
    Sprite sprite;
    RenderComponent(Entity *o, const Color &color = Color::Red) : Component(o)
    {
        sprite.setColor(color);
    }
    RenderComponent(Entity *o, const string TexturePath = "") : Component(o)
    {
        if (!texture.loadFromFile(TexturePath))
        {
            sprite.setColor(Color());
        }
        sprite.setTexture(texture);
        sprite.setOrigin({0, 0});
        sprite.setPosition({0, 0});
        sprite.setScale({1, 1});
    }
    void init() override;
    void update(float deltaTime) override;
    void draw(RenderWindow &window) override { window.draw(sprite); }
};

// a Comoponent that Handling collision
// the current version can handle AABB collision
class ColliderComponent : public Component
{
public:
    ColliderComponent(Entity *o) : Component(o) {}
    FloatRect getBound() const;
};

// handle Velocity, Gravity and Collision responses
class PhysicComponent : public Component
{
public:
    Vector2f velocity{0.f, 0.f};
    float maxSpeed = 200.f;
    float gravity = 900.f;
    bool onGround = false;

    PhysicComponent(Entity *o) : Component(o) {}
    void update(float deltaTime) override;
};

// Hanlde input from the  Player
class InputComponent : public Component
{
public:
    float moveSpeed = 180.f;
    float jumpForce = 420.f;
    InputComponent(Entity *o) : Component(o) {}
    void update(float deltaTime) override;
};

// Camera view
// Default as follows player
class CameraComponent : public Component
{
public:
    View *view = nullptr;
    CameraComponent(Entity *o, View *v) : Component(o), view(v) {}
    void update(float deltaTime) override;
};

class AnimationComponent : public Component
{
public:
    struct Animation
    {
        vector<IntRect> frames;
        float frameTime;
    };

    map<string, Animation> animations;
    string currentAnimation = "Walking";
    int currentFrame = 0;
    float timer = 0.f;

    AnimationComponent(Entity *o) : Component(o) {}
    // Adding new Animation
    void addAnimation(const string &name, const Animation &anim)
    {
        animations[name] = anim;
    }
    // Change the Animation the order one
    void play(const string &name)
    {
        if (currentAnimation != name)
        {
            currentAnimation = name;
            currentFrame = 0;
            timer = 0.f;
        }
    }
    void update(float deltaTime) override;
};

class Entity
{
public:
    int z_index = 0;
    Game *scence = nullptr;
    vector<unique_ptr<Component>> components;
    bool active = true;
    Entity(Game *g) : scence(g) {}

    template <typename T, typename... Args>
    T *addComponent(Args &&...args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        auto ptr = std::make_unique<T>(this, std::forward<Args>(args)...);
        T *raw = ptr.get();
        components.emplace_back(std::move(ptr));
        raw->init();
        return raw;
    }

    template <typename T>
    T *getComponent()
    {
        for (unique_ptr<Component> &comp : components)
        {
            if (T *sastifyComp = dynamic_cast<T *>(comp.get()))
                return sastifyComp;
        }
        return nullptr;
    }

    template <typename T>
    bool hasComponent()
    {
        for (unique_ptr<Component> &comp : components)
        {
            if (T *sastisfyComp = dynamic_cast<T *>(comp.get()))
                return true;
        }
        return false;
    }
    void update(float deltaTime)
    {
        for (unique_ptr<Component> &comp : components)
            comp->update(deltaTime);
    }
    void draw(RenderWindow &window)
    {
        for (unique_ptr<Component> &comp : components)
        {
            comp->draw(window);
        }
    }
};

class TileMap
{
public:
    int z_index = 10;
    int tileSize = 40;
    vector<string> rows;

    Sprite *sprite = nullptr;
    Texture *texture = nullptr;
    bool canInteract = true;

    TileMap(const string _pathDir = "spritesheet_18.jpg", const string tilePath = "file.txt")
    {
        texture = new Texture;
        if (!texture->loadFromFile(_pathDir))
        {
            delete texture;
            texture = nullptr;
            throw(404);
        }
        sprite = new Sprite;
        sprite->setTexture(*texture);
        // simple level layout ('.' empty, '#' solid)
        rows = readFromFile(tilePath);
    }
    TileMap(const string texturePath, const string tilePath, IntRect subRect, bool _canInteract = true)
    {
        texture = new Texture;
        if (!texture->loadFromFile(texturePath))
        {
            delete texture;
            texture = nullptr;
            throw(404);
        }
        sprite = new Sprite;
        sprite->setTexture(*texture);
        sprite->setTextureRect(subRect);

        rows = readFromFile(tilePath);
    }
    ~TileMap()
    {
        if (sprite != nullptr)
            delete sprite;
        if (texture != nullptr)
            delete texture;

        sprite = nullptr;
        texture = nullptr;
    }
    void setColor(const Color color)
    {
        sprite->setColor(color);
    }
    void setIntRect(const IntRect rectangle)
    {
        sprite->setTextureRect(rectangle);
    }
    vector<FloatRect> getSolidTiles() const
    {
        if (!canInteract)
            return vector<FloatRect>{};

        vector<FloatRect> boxes;
        for (size_t r = 0; r < rows.size(); ++r)
        {
            for (size_t c = 0; c < rows[r].size(); ++c)
            {
                if (rows[r][c] == '#')
                {
                    boxes.emplace_back(c * tileSize, r * tileSize, tileSize, tileSize);
                }
            }
        }
        return boxes;
    }

    void draw(RenderWindow &window)
    {
        for (int r = 0; r < rows.size(); ++r)
        {
            for (int c = 0; c < rows[r].size(); ++c)
            {
                if (rows[r][c] == '#')
                {
                    sprite->setPosition(c * tileSize, r * tileSize);
                    window.draw(*sprite);
                }
            }
        }
    }
};

// Scence Manager
class Game
{
public:
    RenderWindow window;
    TileMap tilemap;
    vector<unique_ptr<Entity>> entities;
    Entity *player = nullptr;
    View view;

    Game() : window(VideoMode(853, 480), "Sound")
    {
        window.setFramerateLimit(60);
        view = window.getDefaultView();
    }
    Entity *createEntity()
    {
        unique_ptr<Entity> e = make_unique<Entity>(this);
        Entity *raw = e.get();

        entities.emplace_back(move(e));
        return raw;
    }

    void resolveCollision(Entity *e, bool horizontal)
    {
        TransformComponent *trans = e->getComponent<TransformComponent>();
        ColliderComponent *colli = e->getComponent<ColliderComponent>();
        PhysicComponent *phys = e->getComponent<PhysicComponent>();
        // Entity doesn't have Collision
        if (!trans || !colli || !phys)
            return;

        FloatRect bounds = colli->getBound();
        // check for each tile in the map
        // for (unique_ptr<TileMap> &tilemap : tilemaps)
        // {
        // only check for tilemap that Entity can Interact

        for (FloatRect &tile : tilemap.getSolidTiles())
        {
            // Entity Touched object
            if (tile.intersects(bounds))
            {
                const float px = trans->position.x;
                const float py = trans->position.y;
                // Entity touched left or right of the obstical
                if (horizontal)
                {
                    // Moving left -> snap to the right
                    if (phys->velocity.x < 0)
                    {
                        trans->position.x = tile.left + tile.width + 0.001f;
                    }
                    // Moving right --> snap to the left
                    else if (phys->velocity.x > 0)
                    {
                        trans->position.x = tile.left - trans->size.x - 0.001f;
                    }
                    phys->velocity.x = 0;
                    bounds = colli->getBound();
                }
                // Entity touched ground or ceilling
                else
                {
                    // Falling --> Stand on Top
                    if (phys->velocity.y > 0)
                    {
                        trans->position.y = tile.top - trans->size.y - 0.001f;
                        phys->velocity.y = 0;
                        phys->onGround = true;
                    }
                    // bump head
                    if (phys->velocity.y < 0)
                    {
                        trans->position.y = tile.top + tile.height + 0.001f;
                        phys->velocity.y = 0;
                    }
                    phys->velocity.y = 0;
                    bounds = colli->getBound();
                }
            }
        }
        // }
    }

    void update(float deltaTime)
    {
        // Update entities( components)
        for (unique_ptr<Entity> &e : entities)
            e->update(deltaTime);
        // Simple Camera place at the Center of the Frame
        if (player)
        {
            TransformComponent *trans = player->getComponent<TransformComponent>();

            window.setView(view);
        }
    }

    void draw()
    {
        window.clear();
        int i = 0;

        while (i < entities.size())
            entities[i++]->draw(window);
        // while (j < entities.size())
        //     tilemaps[j++]->draw(window);
        tilemap.draw(window);
        window.display();
    }

    void run()
    {

        tilemap.setIntRect({438, 12, 73, 73});
        tilemap.setColor(Color{0, 19, 25});

        Entity *camE = createEntity();
        camE->addComponent<CameraComponent>(&view);

        playerSetup();
        buildEnviroment();
        
        // Sorting the display order( z_index)
        sort(entities.begin(), entities.end(),
             [](const unique_ptr<Entity> &a, const unique_ptr<Entity> &b)
             { return a->z_index < b->z_index; });

        Clock clock;
        float dt;
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            dt = clock.restart().asSeconds();
            if (dt > 0.05f)
                dt = 0.05; // clamp

            update(dt);
            draw();
        }
    }
    // create controlable character
    void playerSetup() {
        // create a  simple player entity
        player = createEntity();
        player->addComponent<TransformComponent>(Vector2f{80, 200}, Vector2f{64, 64});
        player->addComponent<RenderComponent>("the_girl_walking.png");
        player->addComponent<AnimationComponent>();
        player->addComponent<ColliderComponent>();
        player->addComponent<PhysicComponent>();
        player->addComponent<InputComponent>();

        player->getComponent<RenderComponent>()->sprite.setScale(0.2, 0.2);
        player->getComponent<RenderComponent>()->sprite.scale({10, 10});
        player->getComponent<RenderComponent>()->sprite.setTextureRect({{0, 0}, {32, 32}});
        player->z_index =  10;
        AnimationComponent::Animation anim;
        anim.frameTime = 1.0 / 8;

        IntRect rect({0, 0}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({0, 32}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({0, 64}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({32, 0}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({32, 32}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({32, 64}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({64, 0}, {32, 32});
        anim.frames.push_back(rect);
        rect = IntRect({64, 32}, {32, 32});
        anim.frames.push_back(rect);

        player->getComponent<AnimationComponent>()->addAnimation("Walking", anim);
    }
    // Construct the enviroment including: obsticle, background, decoration
    // it's only  works for the static enviroment without any kind motion
    void buildEnviroment()
    {
        const string filePath = "decorate.txt";
        // Magic const 16
        vector<vector<string>> data = readExcludeSpace(filePath, 16);

        for (int i = 0; i < data.size(); ++i)
        {
            Entity *object = createEntity();

            object->addComponent<RenderComponent>(data[i].back());
            object->addComponent<AnimationComponent>();
            object->addComponent<TransformComponent>();

            // in RenderWindow
            Vector2f position = {toFloat(data[i][1]), toFloat(data[i][2])};
            Vector2f velocity = {toFloat(data[i][3]), toFloat(data[i][4])};
            float gravity = toFloat(data[i][5]);

            int number_of_frame = toInteger(data[i][6]);
            float frame_time = toFloat(data[i][7]);
            // in the sprite sheet
            Vector2i sprite_position = {toInteger(data[i][8]), toInteger(data[i][9])};
            Vector2i sprite_size = {toInteger(data[i][10]), toInteger(data[i][11])};

            int z_index = toInteger(data[i][12]);
            Vector2f scale = {toFloat(data[i][13]), toFloat(data[i][14])};

            IntRect rect(sprite_position, sprite_size);

            AnimationComponent *animComp = object->getComponent<AnimationComponent>();
            RenderComponent *render = object->getComponent<RenderComponent>();
            TransformComponent *trans = object->getComponent<TransformComponent>();

            render->sprite.setTextureRect(rect);
            render->sprite.setScale(scale);
            trans->position = position;

            AnimationComponent::Animation anim;
            anim.frameTime = frame_time;
            anim.frames.push_back(rect);
            animComp->addAnimation("BackGround", anim);
            animComp->play("BackGround");
            object->z_index = z_index;
        }
    }
    void spawnEntity()
    {
    }
};

// --------------------
// Implementation
// --------------------

// get the size and position from TransformComponent
void RenderComponent::init()
{
    if (owner)
    {
        TransformComponent *trans = owner->getComponent<TransformComponent>();
        if (trans)
        {
            sprite.setPosition(trans->position);
        }
    }
}

void RenderComponent::update(float deltaTime)
{
    if (owner)
    {
        TransformComponent *trans = owner->getComponent<TransformComponent>();
        if (trans)
        {
            sprite.setPosition(trans->position);
        }
    }
}

FloatRect ColliderComponent::getBound() const
{
    if (!owner)
        return {0, 0, 0, 0};

    TransformComponent *trans = owner->getComponent<TransformComponent>();
    if (!trans)
        return {0, 0, 0, 0};

    return {trans->position.x, trans->position.y, trans->size.x, trans->size.y};
}

void PhysicComponent::update(float deltaTime)
{
    if (!owner)
        return;
    TransformComponent *trans = owner->getComponent<TransformComponent>();
    if (!trans)
        return;

    // Apply gravity
    velocity.y += gravity * deltaTime;
    onGround = false;

    // Horizontal movement
    trans->position.x += velocity.x * deltaTime;
    // Resolve Horizontal collistion
    if (owner->scence)
        owner->scence->resolveCollision(owner, true);

    // vertical Movement
    trans->position.y += velocity.y * deltaTime;
    // Resolve Vertical collision
    if (owner->scence)
        owner->scence->resolveCollision(owner, false);
}

void InputComponent::update(float delteTime)
{
    if (!owner)
        return;
    PhysicComponent *phys = owner->getComponent<PhysicComponent>();
    AnimationComponent *anim = owner->getComponent<AnimationComponent>();

    if (!phys && !anim)
        return;

    bool action = false; // Standing if there is no action
    float dir = 0.f;
    // Walking
    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
    {
        action = true;
        dir = -1.0f;
        anim->play("Walking");
    }
    if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
    {
        action = true;
        dir = 1.0f;
        anim->play("Walking");
    }
    // Sprinting
    if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) &&
        (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)))
    {
        action = true;
        dir = -2.0f;
        anim->play("Sprinting");
    }
    if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) &&
        (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)))
    {
        action = true;
        dir = 2.0f;
        anim->play("Sprinting");
    }
    // Crounching
    // Set horizontal velocity( instant acceloration for simplicity)
    phys->velocity.x = dir * moveSpeed;

    // Jump
    if ((Keyboard::isKeyPressed(Keyboard::Space)) && phys->onGround)
    {
        action = true;
        phys->velocity.y = -jumpForce;
        phys->onGround = false;
    }
    // update more

    if (!action)
    {
        anim->play("Standing");
    }
}

void CameraComponent::update(float deltaTime)
{
    // We don't need per-entity camera logic here since Game handles follow,
    // but we keep this component to show how a camera can be modelled per-entity.

    view->setSize({720, 405});
}

void AnimationComponent::update(float deltaTime)
{
    // No animation with such name was Found
    if (animations.find(currentAnimation) == animations.end())
    {
        owner->getComponent<RenderComponent>()->sprite.setTextureRect({{0, 0}, {32, 32}});
        return;
    }

    timer += deltaTime;
    Animation &anim = animations[currentAnimation];
    if (timer > anim.frameTime)
    {
        timer = 0.f;
        currentFrame = (currentFrame + 1) % anim.frames.size();
    }

    if (RenderComponent *rend = owner->getComponent<RenderComponent>())
    {
        rend->sprite.setTextureRect(anim.frames[currentFrame]);
    }
}
// ----------------
// Main
// ----------------
int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
        return -1;
    }
    return 0;
}

vector<string> readFromFile(const string filePath)
{
    ifstream input(filePath);

    if (!input.is_open())
    {
        cout << "Error: Unable to Find the file\n";
        throw(404);
    }

    vector<string> content;
    string line;
    while (getline(input, line, '\n'))
    {
        content.push_back(line);
    }

    input.close();
    return content;
}
vector<vector<string>> readExcludeSpace(const string filePath, const int argc = 16)
{
    ifstream input(filePath);

    string infor;
    vector<vector<string>> data;
    while (!input.eof())
    {
        data.push_back(vector<string>{});

        int cnt = 1;
        string str;
        
        while (cnt <= argc) {
            input >> str;
            data.back().push_back(str);

            cnt++;
        }
    }
    input.close();
    return data;
}

int toInteger(string digits)
{
    bool isNegative = false;
    if (digits[0] == '-') {
        isNegative = true;
        digits[0]  = '0';
    }
    int result = 0;
    for (char& digit : digits)
    {
        result = result * 10 + (digit - '0');
    }

    if (isNegative) return - result;
    return result;
}
float toFloat(string digits)
{
    bool isNegative = false;
    if (digits[0] == '-') {
        isNegative = true;
        digits[0]  = '0';
    }

    bool isFloat = false;
    int i = digits.size() - 1;
    // Calculate the decimal part
    float decimal = 0;
    for (; i >= 0; --i)
    {
        if (digits[i] == '.')
        {
            isFloat = true;
            break;
        }
        decimal = decimal / 10.0 + (digits[i] - '0');
    }
    // Calculate the integer part
    int integer = 0;
    for (char digit : digits)
    {
        if (digit == '.')
            break;
        integer = integer * 10 + (digit - '0');
    }

    if (isNegative)
        return - (integer + (isFloat * decimal / 10));
    return integer + (isFloat * decimal / 10);
}
/*
Detailed explanation of components and their roles (readers: this block explains the design):

1) Component (base)
   - Role: Abstract base for all behaviours/attributes that can be attached to an Entity.
   - Why: Promotes composition over inheritance: Entities gain behaviour by assembling components.

2) TransformComponent
   - Role: Holds position, size and rotation of an Entity.
   - Why: Separates raw spatial data from logic & rendering; many other components (Collider, Sprite)
     read/write the transform.

3) SpriteComponent (RenderComponent)
   - Role: Responsible for drawing the entity to the screen. Here we use an sf::RectangleShape.
   - Why: Keeps rendering concerns separate — swapping to a texture or animation system
     only requires altering this component.

4) ColliderComponent
   - Role: Provides an AABB (axis-aligned bounding box) for collision queries.
   - Why: Separates collision geometry from physics and transform; other systems can query
     collision bounds without needing to duplicate box math.

5) PhysicsComponent
   - Role: Handles velocity, gravity integration, and asks the scene to resolve collisions
     after moving. It's the behaviour that makes entities "physics-aware".
   - Why: Keeps kinematics separate from input and rendering. This component is reusable
     for other moving entities (enemies, moving platforms) by tuning parameters.

6) InputComponent
   - Role: Translates player input (keyboard) into changes to the PhysicsComponent (velocity/jump).
   - Why: Keeps control logic separate; swapping control schemes or binding AI to control
     is then trivial (create an AIInput component that writes to physics similarly).

7) CameraComponent
   - Role: (Optional) Demonstrates camera-related behaviour; in this example, actual follow
     logic lives in Game, but CameraComponent is a placeholder showing you can attach
     camera behaviour to an entity.

8) Entity
   - Role: A container that holds components and delegates update/draw to them.
   - Why: Central concept in component-based design: entities are simple IDs/containers,
     components hold data and behaviour.

9) Game / Scene
   - Role: Owns the tilemap and entities; provides world-level functionality such as
     resolving collisions against static tiles and camera control.
   - Why: Separates per-entity behaviour from global systems (tile collisions, rendering order, input mapping, etc.).

Collision strategy used (simple but effective):
 - Axis-separated AABB resolution: first move horizontally and resolve horizontal collisions,
   then move vertically and resolve vertical collisions. This avoids many corner-case "sticking" problems.
 - The scene (Game) knows the static tiles (TileMap) and performs the resolution. This keeps PhysicsComponent
   small and focused on kinematics.

How to extend/improve this minimal project:
 - Replace Rectangle shapes with textures/sprites and add an AnimationComponent.
 - Implement an event or messaging system so components can subscribe to events (e.g. "OnLand").
 - Add an EntityFactory or Prefab system to spawn enemies/pickups.
 - Add friction, acceleration (instead of instant velocity changes), better collision (swept AABB) to avoid tunneling.
 - Implement an actual ECS (Entity-Component-System) for larger projects where system-wide iteration is more efficient.

Controls:
 - A / Left arrow : move left
 - D / Right arrow: move right
 - W / Up arrow / Space: jump

Compilation note:
 - Link against SFML libraries: -lsfml-graphics -lsfml-window -lsfml-system
 - Ensure SFML include/lib paths are set up if using an IDE or MSYS2 on Windows.

*/