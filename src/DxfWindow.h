#ifndef GRADEPRO_DXFWINDOW_H
#define GRADEPRO_DXFWINDOW_H


#include <string>
#include <utility>
#include "imgui.h"
#include "DxfInterface.h"
#include "AbstractWindow.h"

class DxfWindow : public AbstractWindow {
public:
    explicit DxfWindow(std::string title) : AbstractWindow(std::move(title)) {}

    ~DxfWindow();

    void Render() final;
    void HandleEvent(SDL_Event& e) final;

    void LoadDxf(const std::string& filename);

protected:
private:
    float f = 0.0f;
    int counter = 0;
    float scale = 100.f;
    ImVec2 scrollOffset = {0.f, 0.f};

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    DxfInterface* dxfInterface {};

};


#endif //GRADEPRO_DXFWINDOW_H
