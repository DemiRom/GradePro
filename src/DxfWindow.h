#ifndef GRADEPRO_DXFWINDOW_H
#define GRADEPRO_DXFWINDOW_H


#include <string>
#include "imgui.h"
#include "DxfInterface.h"
#include "SDL.h"

class DxfWindow {
public:
    DxfWindow(std::string title);
    ~DxfWindow();

    void Render();

    void HandleEvent(SDL_Event& e);

    void LoadDxf(const std::string& filename);

protected:
private:
    std::string title;
    bool opened = true;
    float f = 0.0f;
    int counter = 0;
    float scale = 100.f;
    ImVec2 scrollOffset = {0.f, 0.f};

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    DxfInterface* dxfInterface {};

};


#endif //GRADEPRO_DXFWINDOW_H
