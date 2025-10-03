
#include "imgui.h"

#include "entity.h"
#include "entityManager.h"

#include "component_editor.h"
#include "animation_editor.h"
// the window that has the left is the list of entity that user can choose, the remaining right part is utiity: component editor, animation editor, etc,...
class EntityEditor {
private:
    size_t current_entityID;

    void DrawPopup();
    void DrawHeirarchyPanel(EntityManager*);
public:
    bool
    pause,
    display_inspector_panel,
    display_entity_information,
    display_animation_editor = false;

    EntityEditor();
    void DrawEntityEditor(bool*);
};