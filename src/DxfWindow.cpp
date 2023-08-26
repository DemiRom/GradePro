#include "DxfWindow.h"

#include <utility>
#include "imgui.h"

DxfWindow::DxfWindow(std::string title) : title (std::move(title)) {

}

DxfWindow::~DxfWindow() = default;

void DxfWindow::Render() {
    ImGui::Begin(this->title.c_str());

//    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//    ImGui::Checkbox("Another Window", &thisshow_another_window);

//    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//    ImGui::ColorEdit3("clear color", (float*)&this->clear_color); // Edit 3 floats representing a color
//
//    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//        counter++;
//
//    ImGui::SameLine();
//    ImGui::Text("counter = %d", counter);

//    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImVec2 p = ImGui::GetCursorScreenPos();

    for(int i = 0; i < 20; i++)
        ImGui::GetWindowDrawList()->AddLine(ImVec2(p.x + 50, p.y+50), ImVec2(i*50 + 1000, i* 50 + 2000), 0xFF0000FF, 1.0f);


    ImGui::End();
}

void DxfWindow::LoadDxf(const std::string &filename) {

}
