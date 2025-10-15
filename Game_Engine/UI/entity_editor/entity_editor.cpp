#include "entity_editor.h"

EntityEditor::EntityEditor() {}

// This function will draw a window that contains a list of exist entities on the left side, the remaining part of  the  window is for other utility such as component editor, entity's information of the current selected entity
// return true if the window is  opened and false if the window closed
void EntityEditor::DrawEntityEditor(bool* is_open)
{

    auto entity_manager = EntityManager::getInstance();

    ComponentEditor comp_editor(entity_manager->findEntity(current_entityID), display_animation_editor);

    ImGui::Begin("Entity Editor", is_open);
    DrawHeirarchyPanel(entity_manager);

    if (display_entity_information)
    {
    }
    if (display_inspector_panel)
    {
        comp_editor.DrawComponentEditor();
    }
    if (display_animation_editor)
    {
        AnimationEditor anim_editor;
        anim_editor.Draw(entity_manager->findEntity(current_entityID), display_animation_editor);
    }
    ImGui::End();
}

// Heirarchy Panel contains all the entity exists and can be access further to entity's component, entity's information by clicking to it
void EntityEditor::DrawHeirarchyPanel(EntityManager *e_manager)
{
    if (ImGui::BeginChild("Entity Hierarchy", {125, 250}, ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY) | ImGuiChildFlags_Borders)
    {
        auto &entities = e_manager->entities;
        for (const std::unique_ptr<Entity> &e : entities)
        {
            if (e->deleted)
                continue;

            ImGui::PushID(e->id);

            // Highlight the Entity if the Entity is chosen
            bool isSelected = (current_entityID == e->id);
            // can be  replace by the name of the Entity

            // adding more feture later on on this part
            if (ImGui::Selectable(e->name.c_str(), isSelected))
            {
                current_entityID = e->id;
                ImGui::OpenPopup("Entity Properties");
            }
            // PopUp option to configurate entity
            DrawPopup();

            ImGui::PopID();
        }

        ImGui::NewLine();

        if (ImGui::Button("Add", {100, 25}))
        {
            size_t id = e_manager->createEntity();
            e_manager->findEntity(id)->name = "Unamed Entity";
        }

        ImGui::NewLine();

        if (ImGui::Button("Erase", {100, 25}))
        {
        }

        ImGui::EndChild();
    }
}

void EntityEditor::DrawPopup()
{
    // this popup will lead user to choose which properties to be displayed
    if (ImGui::BeginPopup("Entity Properties"))
    {
        ImGui::Text("Entity ID: %lu", current_entityID);

        ImGui::NewLine();
        ImGui::Separator();

        if (ImGui::Button("Information"))
        {
            display_entity_information = true;
        }

        ImGui::NewLine();

        if (ImGui::Button("Component Editor"))
        {
            display_inspector_panel = true;
        }

        ImGui::EndPopup();
    }
}