#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "imgui.h"
#include <GL/gl.h>

class TextureEditor;

struct Texture
{
    std::string name = "";
    GLuint id = 0;
    int height = 240, width = 240;
};

GLuint LoadTextureFromFile(const char *filename, int *width, int *height);

template <typename T>
class ResourceManager
{
private:
    static ResourceManager *instance;
    std::unordered_map<std::string, T> container;

    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ~ResourceManager();

public:
    static ResourceManager *getInstance();

    T load(const std::string &, const T);
    T load(const std::string &, const std::string &);

    T get(const std::string &);

    void unload(const std::string &);
};

template <typename T>
inline ResourceManager<T> *ResourceManager<T>::instance = nullptr;

template <>
class ResourceManager<Texture>
{
    friend class TextureEditor;

private:
    static ResourceManager *instance;
    // storage data
    std::unordered_map<std::string, Texture> container;
    // Hidden constructor,  destructor, operator=
    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ~ResourceManager();

public:
    static ResourceManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new ResourceManager<Texture>();
        }
        return instance;
    }

    // Add a new spritesheet/ texture to the database, if the texture with such name  existed then  replace it
    Texture load(const std::string &texture_name, const Texture texture) {
        return container[texture_name] = texture;
    }
    Texture load(const std::string &texture_name, const std::string &objPath)
    {
        if (container.find(texture_name) == container.end())
        {
            Texture texture;
            texture.name = texture_name;
            texture.id = LoadTextureFromFile(objPath.c_str(),
                                             &texture.width, &texture.height);

            container[texture_name] = texture;
        }
        return container[texture_name];
    }
    Texture get(const std::string &texture_name) const
    {
        if (container.empty())
            return {"empty",0,240,240};
        if (auto obj = container.find(texture_name); obj != container.end())
        {
            return obj->second;
        }
        return {"empty",0,240,240};
    }

    void unload(const std::string texture_name)
    {
        container.erase(texture_name);
    }
};

inline ResourceManager<Texture> *ResourceManager<Texture>::instance = nullptr;
