#include "LaserWindow.h"
#include "imgui.h"

void LaserWindow::Render() {
    ImGui::Begin(this->title.c_str(), &this->opened, 0);
//                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
//                 ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Benchmark Settings");

    ImGui::Combo("Benchmark Unit", &benchmarkUnitIndex, "M\0cm\0mm\0");
    ImGui::InputDouble("Benchmark", &benchmark);
    ImGui::InputInt("Benchmark Reading (cm)", &benchmarkReading);
    ImGui::Text("Laser Elevation: %f(m)", laserHeight);
    ImGui::SameLine();

    if (ImGui::Button("Set H/I")) {
        this->laserHeight = benchmark + ((float) benchmarkReading / 100);
        if (this->laserHeight != 0)
            hiSet = true;
    }

    if (hiSet) {

        if (ImGui::CollapsingHeader("Quick Elevation Check")) {
            ImGui::InputInt("Quick Reading (cm)", &gradeReading);
            ImGui::Text("Current Elevation: %f(m)", (laserHeight - ((float) gradeReading / 100)));
        }

        if (ImGui::CollapsingHeader("Expected Elevation Check")) {
            ImGui::InputDouble("Expected Elevation (m)", &expectedElevation);
            ImGui::InputDouble("Offset (m)", &expectedElevationOffset);
            ImGui::Text("Expected Elevation with Vertical offset: %f(m)",
                        (this->expectedElevation + this->expectedElevationOffset));

            ImGui::InputInt("Grade Reading (cm)", &expectedGradeReading);
            double currentElevation = (laserHeight - ((float) this->expectedGradeReading / 100));
            ImGui::Text("Current Elevation: %f(m)", currentElevation);

            ImGui::Text("Cut/Fill: %f (cm)", ((this->expectedElevation + this->expectedElevationOffset) -
                                              (this->laserHeight - ((float) expectedGradeReading / 100))) * 100);

            if (ImGui::CollapsingHeader("Grade Elevation")) {
                ImGui::InputDouble("Slope %", &gradeSlope);
                ImGui::InputInt("Distance (m)", &gradeDistance);
                ImGui::Checkbox("Ascending/Descending", &upDown);

                if (ImGui::BeginTable("Slope Grade", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg,
                                      ImVec2(ImGui::CalcTextSize("A").x * 40, 0.0f))) {

                    for (int row = 1; row <= gradeDistance; row++) {
                        ImGui::TableNextRow();

                        for (int column = 0; column < 3; column++) {
                            ImGui::TableNextColumn();
                            if (column == 0) //Mark
                                ImGui::Text("%i(m)", row);
                            if (column == 1) //Elevations
                                ImGui::Text("%f", expectedElevation + (upDown ? ((this->gradeSlope / 100) * row) : -(
                                        (this->gradeSlope / 100) * row)));
                            if (column == 2) //Grade stick reading
                                ImGui::Text("%f", expectedGradeReading - (upDown ? ((this->gradeSlope) * row) : -(
                                        (this->gradeSlope) * row)));
                        }
                    }
                    ImGui::EndTable();
                }
            }
        }


    }
    ImGui::End();
}

void LaserWindow::HandleEvent(SDL_Event &event) {

}
