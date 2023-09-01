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
//    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.f, 0.f, 0.f, 1.f);

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

    /**
     * Visual Toolbar Buttons
     */
    ImGui::Separator();

    if (ImGui::Button(this->showVertices ? "Hide Vertices" : "Show Vertices"))
        this->showVertices = !this->showVertices;

    ImGui::SameLine();
    if (ImGui::Button(this->showPolylines ? "Hide Polylines" : "Show Polylines"))
        this->showPolylines = !this->showPolylines;

    ImGui::SameLine();
    if (ImGui::Button(this->showLines ? "Hide Lines" : "Show Lines"))
        this->showLines = !this->showLines;

    ImGui::SameLine();
    if (ImGui::Button(this->showPoints ? "Hide Points" : "Show Points"))
        this->showPoints = !this->showPoints;

    ImGui::SameLine();
    if (ImGui::Button(this->showArcs ? "Hide Arcs" : "Show Arcs"))
        this->showArcs = !this->showArcs;

    ImGui::Separator();

    /**
     * Grade Manipulation Buttons
     */

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

        if (this->showLines) {
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
        }

        if (this->showPoints) {
            for (const auto &point: data->points) {
                if (point.z != 0)
                    continue;

                //TODO Add a radius
                windowDrawList->AddCircle(ImVec2((float)point.x * scale + scrollOffset.x, (float)point.y * scale + scrollOffset.y), 2,
                                          0x0000ffff);

            }
        }

        if (this->showVertices) {
            for (const auto &vertex: data->vertex) {
                if (vertex.z != 0) {
                    continue;
                }

                windowDrawList->AddRect(ImVec2(
                                                (((float) vertex.x * scale) + (scrollOffset.x + p.x)) - 1,
                                                (((float) vertex.y * scale) + (scrollOffset.y + p.y)) - 1),
                                        ImVec2(
                                                (((float) vertex.x * scale) + (scrollOffset.x + p.x)) + 1,
                                                (((float) vertex.y * scale) + (scrollOffset.y + p.y)) + 1),
                                        0xffffffff);
            }
        }

        if (this->showPolylines) {
            for (const auto &polyline: data->polylines) {

                assert(polyline.polyline.number == polyline.vertices.size());

                for (int i = 0; i <= polyline.polyline.number; i++) {
                    if (i + 1 >= polyline.polyline.number)
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
        }

        if (this->showArcs) {//TODO This is not an arc
            for (const auto &arc: data->arcs) {
                if (arc.cz != 0)
                    continue;

                windowDrawList->AddCircle(ImVec2((float)arc.cx * scale + scrollOffset.x, (float)arc.cy * scale + scrollOffset.y),
                                          (float)arc.radius,
                                          0xffffffff);
            }
        }
    }
//TODO Set the style to change background colors
    ImGui::EndChild();

//    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);

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
            this->scrollOffset.x = (-(this->scrollOffsetStartPosition.x - e.motion.x) + this->scrollOffset.x) * (100.f / this->scale);
            this->scrollOffset.y = (-(this->scrollOffsetStartPosition.y - e.motion.y) + this->scrollOffset.y) * (100.f / this->scale);
        }
    } else {
        this->scrollOffsetStartPosition.x = e.motion.x;
        this->scrollOffsetStartPosition.y = e.motion.y;
    }

    if(e.key.keysym.sym == SDL_KeyCode::SDLK_r) {
        this->scrollOffset = {0.f, 0.f};
    }
}

