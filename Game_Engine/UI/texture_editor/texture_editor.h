#include <GL/gl.h>

#include "imgui.h"

#include "component.h"
#include "resourceManager.hpp"

class TextureEditor {
private:
    Texture current_texture;

    void DisplayTexture();

    void DrawButton();
    void DrawSelectedMenu();
    void DrawPopUp();

public:
    TextureEditor();
    // draw the sprite sheet/ image/ texture of the selected entity
    void Draw(bool*);
};

