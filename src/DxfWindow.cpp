#include "DxfWindow.h"

#include <utility>
#include <iostream>
#include "imgui.h"
#include "FileDialog.h"
#include "dl_dxf.h"
#include "dl_codes.h"

DxfWindow::DxfWindow(std::string title) : title(std::move(title)) {
}

DxfWindow::~DxfWindow() {
    delete this->dxfInterface;
};

void DxfWindow::Render() {
    ImGui::Begin(this->title.c_str(), &opened,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginMenuBar()) {

        ImGui::EndMenuBar();
    }

    ImGui::SameLine();
    if (ImGui::Button("Open CAD File"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".dxf,.dwg", ".");

    ImGui::SameLine();
    if (ImGui::Button("+"))
        this->scale += 5;

    ImGui::SameLine();
    if (ImGui::Button("-"))
        this->scale -= 5;

    ImGui::SameLine();
    ImGui::Text("Zoom: %f", this->scale);

    ImGui::Separator();
    ImGui::BeginChild("WindowContents");

//    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0, 0);



    if (this->dxfInterface != nullptr) {
        ImVec2 p = ImGui::GetCursorScreenPos();
        auto windowDrawList = ImGui::GetWindowDrawList();

        auto *data = this->dxfInterface->getDxfData();
        auto attributes = dxfInterface->getAttributes();
//            std::cout << "Colour: " << attributes.getColor() << std::endl;

        double r = dxfColors[attributes.getColor()][0];
        double g = dxfColors[attributes.getColor()][1];
        double b = dxfColors[attributes.getColor()][2];

        int r_s = floor(r >= 1.0 ? 255 : r * 256.0);
        int g_s = floor(g >= 1.0 ? 255 : g * 256.0);
        int b_s = floor(b >= 1.0 ? 255 : b * 256.0);

        int colour = (r_s << 24) |
                     (g_s << 16) |
                     (b_s << 8) |
                     0x000000ff;


        std::cout << this->dxfInterface->getWidth() << std::endl;
        std::cout << this->dxfInterface->getHeight() << std::endl;

        for (const auto &line: data->lines) {
            windowDrawList->AddLine(ImVec2(
                                            (((float) line.x1 * scale) + (scrollOffset.x + p.x)),
                                            (((float) line.y1 * scale) + (scrollOffset.y + p.y))),
                                    ImVec2(
                                            (((float) line.x2 * scale) + (scrollOffset.x + p.x)),
                                            (((float) line.y2 * scale) + (scrollOffset.y + p.y))),
                                    0xFF0000FF,
                                    1.f);
        }

        for (const auto &vertex: data->vertex) {
            if (vertex.z != 0)
                continue;

            windowDrawList->AddRect(ImVec2(
                                                  (((float) vertex.x * scale) + (scrollOffset.x + p.x)) - 1,
                                                  (((float) vertex.y * scale) + (scrollOffset.y + p.y)) - 1),
                                          ImVec2(
                                                  (((float) vertex.x * scale) + (scrollOffset.x + p.x)) + 1,
                                                  (((float) vertex.y * scale) + (scrollOffset.y + p.y)) + 1),
                                          0xffffffff);
        }

        for (const auto &point : data->points) {
            if(point.z != 0)
                continue;

            //TODO Add a radius
            windowDrawList->AddCircle(ImVec2(point.x * scale + scrollOffset.x, point.y * scale + scrollOffset.y), 2,
                                      0x0000ffff);

        }

        for (const auto &polyline: data->polylines) {

            assert(polyline.polyline.number == polyline.vertices.size());

            for(int i = 0; i <= polyline.polyline.number; i++) {
                if(i + 1 >= polyline.polyline.number)
                    break;

                auto v_a = polyline.vertices.at(i);
                auto v_b = polyline.vertices.at(i + 1);

                windowDrawList->AddLine(ImVec2(
                                                (((float) v_a.x * scale) + (scrollOffset.x + p.x)),
                                                (((float) v_a.y * scale) + (scrollOffset.y + p.y))),
                                        ImVec2(
                                                (((float) v_b.x * scale) + (scrollOffset.x + p.x)),
                                                (((float) v_b.y * scale) + (scrollOffset.y + p.y))),
                                        0xaa0000ff,
                                        1.0f);
            }
        }

        //TODO This is not an arc
        for (const auto &arc: data->arcs) {
            if (arc.cz != 0)
                continue;

            windowDrawList->AddCircle(ImVec2(arc.cx * scale + scrollOffset.x, arc.cy * scale + scrollOffset.y), arc.radius,
                                      0xffffffff);
        }

    }

    ImGui::EndChild();

    /**
     * Open File Dialog Rendering
     */
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk()) {
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
    this->dxfInterface = new DxfInterface();

    auto *dxf = new DL_Dxf();

    if (!dxf->in(filename, this->dxfInterface)) {
        std::cerr << filename << " could not be opened!";
    }

    delete dxf;
}

void DxfWindow::HandleEvent(SDL_Event &e) {
    if(e.type == SDL_EVENT_MOUSE_WHEEL) {
//        std::cout << e.wheel.x << " y " << e.wheel.y << std::endl;
        this->scale += e.wheel.y;
    }

    if(e.type == SDL_EVENT_MOUSE_MOTION) {
        if(e.button.button == SDL_BUTTON_MIDDLE) {
            this->scrollOffset.x = e.motion.x;
            this->scrollOffset.y = e.motion.y;
        }
    }
}

