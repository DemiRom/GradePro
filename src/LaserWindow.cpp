#include "LaserWindow.h"
#include "imgui.h"

void LaserWindow::Render() {

}

void LaserWindow::HandleEvent(SDL_Event &event) {
    ImGui::Begin(this->title.c_str(), &this->opened,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_AlwaysAutoResize);



    ImGui::End();
}
