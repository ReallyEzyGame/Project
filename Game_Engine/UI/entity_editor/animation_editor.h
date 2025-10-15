#include "entity.h"
#include "system.h"
#include "component.h"

#include "entityManager.h"
#include "resourceManager.hpp"

#define _BUFFER_SIZE 128

class AnimationEditor {
public:
    bool display_animation_editor;
    bool pause;
    
    void Draw(Entity*, bool&);        // Draw all UI in the Animation Editor
private:

    void DisplayAnimtion(AnimationComponent*,RenderComponent* ,const Texture&) const;

    void DrawPopUpMenu(AnimationComponent*, RenderComponent*);
    void DrawButton(AnimationComponent*, RenderComponent* , bool&);
    void DrawImage(AnimationComponent*,  RenderComponent*, const Texture&) const;
    void DrawTimeline();
    void DrawInputBox(AnimationComponent*,  RenderComponent*);
};


GLuint LoadTextureFromFile(const char*, int*, int*);