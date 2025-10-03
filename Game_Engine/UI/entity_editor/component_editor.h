#include "entity.h"
#include "entityManager.h"
#define _BUFFER_SIZE 128


class ComponentEditor{
private:
    Entity* selected_entity;

    void DrawPopup();
    void DrawEntitySelectable();
public:
    bool pause,
    &is_open;

    ComponentEditor(Entity*, bool&);
    void DrawComponentEditor();
    
};