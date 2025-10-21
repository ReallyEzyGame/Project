#include "component_editor.h"

ComponentEditor::ComponentEditor(Entity *e, bool& display) : selected_entity(e), is_open(display)  {}

void ComponentEditor::DrawComponentEditor()
{
    DrawEntitySelectable();
}

void ComponentEditor::DrawEntitySelectable()
{
    ImGui::SetCursorPos({200, 25});
    ImGui::BeginChild("Inspector", {100, 100}, ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY | ImGuiChildFlags_Borders);

    if (selected_entity != nullptr)
    {
        // Writitng for all component then add there widgets
        if (selected_entity->hasComponent<TransformComponent>() &&
            ImGui::CollapsingHeader("TransformComponent"))
        {
            auto tran = selected_entity->getComponent<TransformComponent>();

            float position[2] = {tran->position.x, tran->position.y};
            float rotation = tran->rotation;

            ImGui::Text("position");
            ImGui::SameLine();
            if (ImGui::InputFloat2("##position", position))
            {
                tran->position.x = position[0];
                tran->position.y = position[1];
            }

            ImGui::NewLine();
            ImGui::Text("rotation");
            ImGui::SameLine();
            if (ImGui::InputFloat("##rotation", &rotation))
            {
                rotation = rotation < 0 ? 0 : rotation;
                rotation = 360 < rotation ? 360 : rotation;
                tran->rotation = rotation;
            }
        }
        if (selected_entity->hasComponent<PhysicComponent>() &&
            ImGui::CollapsingHeader("PhysicComponent"))
        {
            auto phys = selected_entity->getComponent<PhysicComponent>();

            float velocity[2] = {phys->velocity.x, phys->velocity.y};
            float mass = phys->mass,
                  gravity = phys->gravity,
                  friction = phys->friction;
            bool onGround = phys->onGround,
                 isGravityApplied = phys->isGravityApplied;

            ImGui::Text("velocity");
            ImGui::SameLine();

            if (ImGui::InputFloat2("##velocity", velocity))
            {
                phys->velocity.x = velocity[0];
                phys->velocity.y = velocity[1];
            }

            ImGui::NewLine();
            ImGui::Text("mass");
            ImGui::SameLine();

            if (ImGui::InputFloat("##mass", &mass))
            {
                phys->mass = mass;
            }

            ImGui::NewLine();
            ImGui::Text("friction");
            ImGui::SameLine();

            if (ImGui::DragFloat("##friction", &friction, 1.0f, 0.0f, 5.0f))
            {
                phys->friction = friction;
            }

            ImGui::NewLine();
            ImGui::Text("gravity");
            ImGui::SameLine();

            if (ImGui::InputFloat("##gravity", &gravity))
            {
                phys->gravity = gravity;
            }

            ImGui::NewLine();
            ImGui::Text("applied gravity");
            ImGui::SameLine();

            if (ImGui::Checkbox("##appplied gravity", &isGravityApplied))
            {
                phys->isGravityApplied = isGravityApplied;
            }
        }

        if (selected_entity->hasComponent<InputComponent>() &&
            ImGui::CollapsingHeader("InputComponent"))
        {
            auto inpu = selected_entity->getComponent<InputComponent>();
        }
        if (selected_entity->hasComponent<RenderComponent>() &&
            ImGui::CollapsingHeader("RenderComponent"))
        {
            auto rend = selected_entity->getComponent<RenderComponent>();
            auto tran = selected_entity->getComponent<TransformComponent>();

            static float color[4] = {0, 0, 0, 0}, scale[2] = {0, 0};

            static float size[2] = {0, 0};

            static char buffer[_BUFFER_SIZE];

            ImGui::NewLine();
            ImGui::Text("color");
            ImGui::SameLine();

            if (ImGui::ColorEdit4("##color", color, ImGuiColorEditFlags_AlphaPreview))
            {
                rend->color.Value.x = color[0] < 0 ? 0 : color[0];
                rend->color.Value.x = 255 < color[0] ? 255 : color[0];

                rend->color.Value.y = color[1] < 0 ? 0 : color[1];
                rend->color.Value.y = 255 < color[1] ? 255 : color[1];

                rend->color.Value.z = color[2] < 0 ? 0 : color[2];
                rend->color.Value.z = 255 < color[2] ? 255 : color[2];

                rend->color.Value.w = color[3] < 0 ? 0 : color[3];
                rend->color.Value.w = 255 < color[3] ? 255 : color[3];
            }

            ImGui::NewLine();

            ImGui::Text("texture");

            ImGui::SameLine();

            if (ImGui::InputText("##texture", buffer, _BUFFER_SIZE))
                rend->texture_name = buffer;

            ImGui::NewLine();

            ImGui::Text("Size: ");

            ImGui::SameLine();

            if (ImGui::InputFloat2("##size", size))
            {
                rend->size.x = size[0] > 0 ? size[0] : 0;
                rend->size.y = size[1] > 0 ? size[1] : 0;
            }

            ImGui::NewLine();

            ImGui::Text("Scale: ");

            ImGui::SameLine();

            if (ImGui::InputFloat2("##scale", scale))
            {
                rend->scale.x = scale[0] > 0 ? scale[0] : 1;
                rend->scale.y = scale[1] > 0 ? scale[1] : 1;
            }
        }

        if (selected_entity->hasComponent<AnimationComponent>() &&
            ImGui::Button("AnimationComponent"))
        {
            is_open = true;
        }

        ImGui::Separator();
        if (ImGui::Button("Entity Infor", {100, 20}))
        {
            ImGui::OpenPopup("Entity Data");
        }
        DrawPopup();


        ImGui::NewLine();
        // Adding new component to the current selected Entity
        if (ImGui::Button("Add Component", {100, 20}))
        {
            ImGui::OpenPopup("New Component List");
        }
        else
        {
            ImGui::Text("No entity selected");
        }

    }
    ImGui::EndChild();
}

void ComponentEditor::DrawPopup()
{
    // Edit Entity Data information
    if (ImGui::BeginPopupModal("Entity Data"))
    {
        static char name[_BUFFER_SIZE];
        ImGui::Text("ID: %lu", selected_entity->id);

        ImGui::NewLine();

        ImGui::Text("Name: ");
        ImGui::SameLine();
        if (ImGui::InputText("##Name", name, _BUFFER_SIZE))
            ;

        ImGui::NewLine();

        if (ImGui::Button("Cancel", {50, 25}))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("OK", {50, 25}))
        {
            selected_entity->name = name;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }


    // Adding new Component
    if (ImGui::BeginPopup("New Component List"))
    {
        if (!selected_entity->hasComponent<AnimationComponent>() && ImGui::MenuItem("Animation"))
        {
            selected_entity->addComponent<AnimationComponent>();
        }
        if (!selected_entity->hasComponent<InputComponent>() && ImGui::MenuItem("Input"))
        {
            selected_entity->addComponent<InputComponent>();
        }
        if (!selected_entity->hasComponent<PhysicComponent>() && ImGui::MenuItem("Physic"))
        {
            selected_entity->addComponent<PhysicComponent>();
        }
        if (!selected_entity->hasComponent<TransformComponent>() && ImGui::MenuItem("Transform"))
        {
            selected_entity->addComponent<TransformComponent>();
        }
        if (!selected_entity->hasComponent<RenderComponent>() && ImGui::MenuItem("Render"))
        {
            selected_entity->addComponent<RenderComponent>();
        }

        ImGui::EndPopup();
    }
}