#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"


#include "system.h"
#include "entity_editor.h"
#include "texture_editor.h"


GLuint LoadTextureFromFile(const char *filename, int *width, int *height)
{
    // get surface
    SDL_Surface *surface = IMG_Load(filename);
    if (!surface)
    {
        std::cerr << "Failed to load Image\n";
        return 0;
    }
    // get rect size of the image
    *width = surface->w;
    *height = surface->h;
    // Create New Texture
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    // configuration
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // upload image to GPU
    // convere SDL_Surface -->  GL_RGBA
    GLenum format;
    if (surface->format->BytesPerPixel == 4)
    {
        format = GL_RGBA;
    }
    else if (surface->format->BytesPerPixel == 3)
    {
        format = GL_RGB;
    }
    else
    {
        SDL_FreeSurface(surface);
        std::cerr << "Undetect such pixel format\n";
        return 0;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
    return image_texture;
}



class GameEngine
{
private:
    static GameEngine *instance;

    bool pause = false, done = false;
    bool display_entity_heirarchy_panel = false,
        display_entity_editor = false,
        display_texture_editor = false,
        display_action_editor = false;

    unsigned long long dt1, dt2;



    SDL_GLContext gl_context;
    SDL_Window *window;


    EntityEditor e_editor;
    TextureEditor texture_editor;


    EntityManager *entity_manager = EntityManager::getInstance();


    RenderSystem *rend_sys = RenderSystem::getInstance();
    AnimationSystem *anim_sys = AnimationSystem::getInstance();
    PhysicSystem *phys_sys = PhysicSystem::getInstance();


    GameEngine() {}
    GameEngine(const GameEngine &) = delete;
    ~GameEngine()
    {
        if (instance != nullptr)
            delete instance;
        instance = nullptr;
    }


public:
    static GameEngine *getInstance();
    void Configuaration();
    void Running();
    void RenderWindow();
    void End();
};



GameEngine *GameEngine::instance = nullptr;
GameEngine *GameEngine::getInstance()
{
    if (instance == nullptr)
        instance = new GameEngine();
    return instance;
}



void GameEngine::Configuaration()
{

}
void GameEngine::Running()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        throw std::runtime_error("Failed to Initialized SDL");
    }
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        throw std::runtime_error("Unable to Initialized PNG or JPG file");
    }
    // config GL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow("Game Engine 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, window_flags);

    // create OpeGL from window
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Turn V-Sync

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw std::runtime_error("Failer to Initialized GLEW ");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

    // Config the style color for ImGui
    ImGui::StyleColorsDark();
    // Initialize Backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");


    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
        }

        dt2 = SDL_GetTicks64();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();


        // Draw here
        RenderWindow();

        // render
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        // Update Entity
        if (!pause)
        {
            float delta = (dt2 - dt1) / 1000.f;
            rend_sys->update(delta);
            phys_sys->update(delta);
            anim_sys->update(delta);
        }
        dt1 = dt2;
    }

    // glDeleteTextures(1, &image_texture);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
void GameEngine::End()
{
}

void GameEngine::RenderWindow() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::Button("Entity")) {
            display_entity_editor = true;
        }

        ImGui::SameLine();

        if (ImGui::Button("Texture")) {
            display_texture_editor = true;
        }
        if (ImGui::Button("Action")) {
            display_action_editor = true;
        }

        ImGui::EndMainMenuBar();
    }
    

    if (display_entity_editor)
        e_editor.DrawEntityEditor(&display_entity_editor);
    if (display_texture_editor)
        texture_editor.Draw(&display_texture_editor);
    if (display_action_editor);     // display action editor
}




int main(int agrc, char *argv[])
{
    GameEngine *engine = GameEngine::getInstance();

    engine->Configuaration();
    engine->Running();
    engine->End();

    return 0;
}
