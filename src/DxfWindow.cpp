#include "DxfWindow.h"

#include <utility>
#include <iostream>
#include "imgui.h"
#include "FileDialog.h"

DxfWindow::DxfWindow(std::string title) : title(std::move(title)) {
}

DxfWindow::~DxfWindow() = default;

void DxfWindow::Render() {
    ImGui::Begin(this->title.c_str());

    if(ImGui::BeginMenuBar()) {

        ImGui::EndMenuBar();
    }

    ImGui::SameLine();

    if (ImGui::Button("Open CAD File"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".dxf,.dwg", ".");
    ImGui::SameLine();

    if (ImGui::Button("+"))
        std::cout << "Zoom in" << std::endl;
    ImGui::SameLine();

    if (ImGui::Button("-"))
        std::cout << "Zoom out" << std::endl;

    ImGui::Separator();
    ImGui::BeginChild("WindowContents");

//    ImGui::SameLine();
//    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0, 0);

//    if (this->data != nullptr) {
//        ImVec2 p = ImGui::GetCursorScreenPos();
//        auto windowDrawList = ImGui::GetWindowDrawList();

//        for (const auto &layer: this->data->layers) {
//            windowDrawList->AddLine(ImVec2(p.x + 50, p.y + 50), ImVec2(1000, 2000), layer.color,
//                                                layer.lWeight);
//        }
//        for(const auto& lineType : this->data->lineTypes) {
//            windowDrawList->AddLine(ImVec2(p.x + lineType.path[0]))
//        }
//        this->data->lineTypes.back()->
//    }

//    for(int i = 0; i < 20; i++)

    ImGui::EndChild();

    /**
     * Open File Dialog Rendering
     */
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            LoadDxf(filePathName);
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }

    ImGui::End();
}

void DxfWindow::LoadDxf(const std::string &filename) {
//    dxfIface.fileImport(filename, this->data);
}
