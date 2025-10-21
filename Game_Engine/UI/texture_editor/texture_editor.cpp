#include "texture_editor.h"

struct Texture;

GLuint LoadTextureFromFile(const char *, int *, int *);

TextureEditor::TextureEditor() {}

// Contains texture, sprite sheet, invisible rectangle
// Help to interract texture that can click to open the information

void TextureEditor::DisplayTexture()
{
    auto texture_manager = ResourceManager<Texture>::getInstance();
    const int height = 50, width = 50;

    if (ImGui::BeginChild("Textures Display", {120, 60}, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY))
    {
        // Display a  set of  all sprite sheets, textures have been loaded
        for (auto &iterator : texture_manager->container)
        {
            Texture texture = iterator.second;
            ImGui::Image(texture.id, {width, height});

            if (ImGui::IsItemHovered() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                // Display all the item that get the Item information when click to it
                ImGui::OpenPopup("texture information");
            }
        }

        // user can click it to get it information
        // user can  add more or remove  less

        // Display the Texture Set
        ImGui::EndChild();
    }
}

void TextureEditor::DrawButton()
{
    // Add a New texture, if no texture with such name  was found then default  texture with ID 0
    ImGui::SetCursorPos({300, 50});
    if (ImGui::Button("Add", {50, 25}))
    {
        ImGui::OpenPopup("Add Texture");
    }
}

void TextureEditor::DrawSelectedMenu() {}

void TextureEditor::DrawPopUp()
{
    // Adding new Texture
    // if the texture file was not found then  using the texture has id 0 (a full color black theme)
    if (ImGui::BeginPopupModal("Add Texture"))
    {
        // name of the  texture
        static char texture_buffer[128];
        static char file_buffer[128];
        Texture texture;

        // the file contains texture must be place in assert/texture
        ImGui::Text("Texture Name: ");
        ImGui::SameLine();
        if (ImGui::InputText("##Texture", texture_buffer, 128));

        ImGui::NewLine();

        ImGui::Text("File Name: ");
        ImGui::SameLine();
        if (ImGui::InputText("##File Name", file_buffer, 128));

        ImGui::NewLine();

        if (ImGui::Button("Cancel", {50, 25}))
            ImGui::CloseCurrentPopup();

        ImGui::SameLine();

        if (ImGui::Button("OK", {50, 25}))
        {
            texture.id = LoadTextureFromFile(file_buffer,
                                             &texture.width, &texture.height);

            texture.name = texture_buffer;

            ResourceManager<Texture>* texture_manager = ResourceManager<Texture>::getInstance();
            texture_manager->load(texture_buffer, texture);

            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    // display the current texture information
    if (ImGui::BeginPopup("texture information"))
    {
        // Magic const at this  position need to be replace or clearly explanation
        ImGui::Image(current_texture.id, {360, 240});

        ImGui::NewLine();
        ImGui::Text("ID: %lu", (unsigned long)current_texture.id);

        ImGui::NewLine();
        ImGui::Text("Name: %s", current_texture.name.c_str());

        ImGui::EndPopup();
    }
}

// pointer to  the boolean for open/close
// is_open can be null means the window doesn't have open/close symbol
void TextureEditor::Draw(bool* is_open)
{
    
    if(ImGui::Begin("Texture Window", is_open)) {

    DisplayTexture();
    DrawPopUp();

    DrawButton();
    DrawSelectedMenu();
    }
    ImGui::End();
}