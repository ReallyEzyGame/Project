#include "animation_editor.h"

// Draw all UI in the Animation AnimationEditor
void AnimationEditor::Draw(Entity *selected_entity, bool &close)
{
    if (!selected_entity)
        return;

    ResourceManager<Texture> *texture_manager = ResourceManager<Texture>::getInstance();
    auto anim = selected_entity->getComponent<AnimationComponent>();
    auto rend = selected_entity->getComponent<RenderComponent>();


    if (!rend || !anim)
        return;


    ImGui::Begin("Animation Editor", &close);

    DisplayAnimtion(anim, rend, texture_manager->get(rend->texture_name));
    DrawPopUpMenu(anim, rend);
    DrawButton(anim, rend, pause);
    DrawImage(anim, rend, texture_manager->get(rend->texture_name));
    DrawInputBox(anim, rend);
    DrawTimeline();

    ImGui::End();
}

// Draw a single animation to the view port
void AnimationEditor::DisplayAnimtion(AnimationComponent *anim, RenderComponent *rend, const Texture &texture) const
{
    // Animartion Display
    ImGui::SetCursorPos({25, 25});
    ImGui::BeginChild("display", {480, 260}, ImGuiChildFlags_Border);
    // Put  the Animation
    ImVec2 top_left = {rend->crop.x, rend->crop.y};
    ImVec2 bottom_right = {rend->crop.z, rend->crop.w};

    ImGui::Image(texture.id, rend->size, top_left, bottom_right);
    ImGui::EndChild();
}

void AnimationEditor::DrawPopUpMenu(AnimationComponent *anim, RenderComponent *rend)
{
    // this group of buttons contains utility for adding, removing,etc... on animation and frame
    // configuration, edit each frame of an Animation
    ImGui::SetCursorPos({550, 25});
    ImGui::BeginChild("Menu", {300, 50}, true);

    if (ImGui::Button("Add Animation"))
    {
        ImGui::OpenPopup("add_animation");
    }

    ImGui::SameLine();

    if (ImGui::Button("Add Frame")) {
        ImGui::OpenPopup("Add Frame");
    }

    ImGui::SameLine();

    if (ImGui::Button("Remove Frame")) {
        ImGui::OpenPopup("Remove Frame");
    }

    // Add a new  frame to the last position of the current animation
    if (ImGui::BeginPopupModal("Add Frame"))
    {
        static float vec2_1[2] = {0, 0}; // Cordinate of top left, bottom right
        static float vec2_2[2] = {0, 0};

        ImGui::Text("Animation: %s", anim->current_animation.c_str());

        ImGui::NewLine();

        ImGui::Text("Top Left Cordinate");

        ImGui::SameLine();

        ImGui::InputFloat2("##XY", vec2_1);

        ImGui::Text("Bottom Right Cordinate");

        ImGui::SameLine();
        
        ImGui::InputFloat2("##ZW", vec2_2);

        ImGui::Separator();

        ImGui::NewLine();
        
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();
        
        ImGui::SameLine();

        if (ImGui::Button("OK"))
        {
            anim->animation.frames.push_back(ImVec4{vec2_1[0], vec2_1[1], vec2_2[0], vec2_2[1]});

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    // Remove the frame (i - 1)-th index
    if (ImGui::BeginPopupModal("Remove Frame"))
    {
        static int frame_num = 0;
        ImGui::Text("Frame: ");
        ImGui::SameLine();
        if (ImGui::InputInt("##FrameRemove", &frame_num))
            ;


        ImGui::NewLine();
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();

        if (ImGui::Button("OK"))
        {
            if (frame_num >= 0 && frame_num < anim->animation.frames.size())
            {
                for (int i = frame_num; i < anim->animation.frames.size() - 1; ++i)
                {
                    anim->animation.frames[i] = anim->animation.frames[i + 1];
                }
                anim->animation.frames.pop_back();
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // Adding a new Animation
    if (ImGui::BeginPopupModal("add_animation")) {
        static int size = 0;
        static char anim_name[_BUFFER_SIZE] = "static";
        AnimationComponent::Animation animation;

        if (ImGui::InputText("##animation name", anim_name, _BUFFER_SIZE));
        
        ImGui::NewLine();

        if (ImGui::InputInt("##frames", &size));

        ImGui::NewLine();

        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();

        ImGui::SameLine();

        if (ImGui::Button("OK")) {
            size = (size > 0) ? size : 1;
            animation.frames = std::vector<ImVec4>(size);

            anim->addAnimation(anim_name, animation);

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }


    ImGui::EndChild();
}
void AnimationEditor::DrawButton(AnimationComponent *anim, RenderComponent *rend, bool &pause)
{
    // Button for moving to the previous, next frame
    // Play, Pause Animation
    ImGui::SetCursorPos({100, 250});
    ImGui::BeginChild("##Animation State", {200, 65}, ImGuiChildFlags_Border);
    // Moving to the previous  frame
    // if there is no frame infront then move to the last frame
    if (ImGui::Button("Previous Frame", {50, 50}))
    {

        anim->timer = 0;
        anim->frame = (anim->frame == 0) ? anim->animation.frames.size() - 1 : anim->frame - 1;
    }
    ImGui::SameLine();
    // Play/Stop an Animation by Clicking it
    if (ImGui::Button("Play", {50, 50}))
    {
        pause = !pause;
    }
    ImGui::SameLine();
    // Moving to the next Frame
    // if there is no frame after it then move to the first  Frame
    if (ImGui::Button("Next Frame", {50, 50}))
    {
        anim->timer = 0;
        anim->frame = (anim->frame == (anim->animation.frames.size() - 1)) ? 0 : anim->frame + 1;
    }
    ImGui::EndChild();

}

void AnimationEditor::DrawImage(AnimationComponent *anim, RenderComponent *rend, const Texture &texture) const
{
    // Display all the frame of the Animation
    ImGui::SetCursorPos({25, 325});
    ImGui::BeginChild("Frame Time", {100, 100},
                      ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY,
                      ImGuiWindowFlags_HorizontalScrollbar);
    for (ImVec4 &crop : anim->animation.frames)
    {
        ImVec2 top_left = {crop.x, crop.y};
        ImVec2 bottom_right = {crop.z, crop.w};

        ImGui::Image(texture.id, rend->size, top_left, bottom_right);

        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            ;

        ImGui::SameLine(0.f, 0.f);
    }
    ImGui::NewLine();
    ImGui::EndChild();
}
void AnimationEditor::DrawTimeline() {}
void AnimationEditor::DrawInputBox(AnimationComponent *anim, RenderComponent *rend)
{
    // Aniamtion Configuration
    ImGui::SetCursorPos({550, 75});
    ImGui::BeginChild("Animation Configuration");

    static char buffer_texture[_BUFFER_SIZE];
    static char buffer_animation[_BUFFER_SIZE];
    float timer = anim->timer;
    int frame = anim->frame;

    if (!rend->texture_name.empty())
        strcpy(buffer_texture, rend->texture_name.c_str());
    if (!anim->current_animation.empty())
        strcpy(buffer_animation, anim->current_animation.c_str());
    // Get the Specific Animation with the Given name
    // If no Animation with such name => default black theme
    ImGui::Text("Texture name");
    ImGui::SameLine();
    if (ImGui::InputText("##current_texture", buffer_texture, _BUFFER_SIZE))
    {
        std::string texture_name = buffer_texture;
        // Create a function that find the texture and all it's rend, anim, trans
        rend->texture_name = texture_name;
    }

    // display the current animation with the input  name
    // if no animation with such  name was found the play current animation
    ImGui::Text("Current Animation");
    ImGui::SameLine();
    if (ImGui::InputText("##current_animtion", buffer_animation, _BUFFER_SIZE))
    {
        anim->play(std::string(buffer_animation));
    }
    ImGui::EndChild();
}
