#ifndef GRADEPRO_DXFWINDOW_H
#define GRADEPRO_DXFWINDOW_H


#include <string>
#include "imgui.h"
#include "DxfInterface.h"

class DxfWindow {
public:
    DxfWindow(std::string title);

    ~DxfWindow();

    void Render();

    void LoadDxf(const std::string &filename);

protected:
private:
    std::string title;
    bool opened = true;

    bool showVertices = false,
            showPolylines = true,
            showLines = true,
            showPoints = true,
            showArcs = false;

    float f = 0.0f;
    int counter = 0;
    float scale = 100.f;
    ImVec2 scrollOffset = {0.f, 0.f};

    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    DxfInterface *dxfInterface{};

};


#endif //GRADEPRO_DXFWINDOW_H
