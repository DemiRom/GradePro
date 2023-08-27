#ifndef GRADEPRO_DXFWINDOW_H
#define GRADEPRO_DXFWINDOW_H


#include <string>
#include "imgui.h"
//#include "DxfIFace.h"

class DxfWindow {
public:
    DxfWindow(std::string title);
    ~DxfWindow();

    void Render();

    void LoadDxf(const std::string& filename);

protected:
private:
    std::string title;
    float f = 0.0f;
    int counter = 0;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//    DxfIFace dxfIface;
//    dx_data* data;
};


#endif //GRADEPRO_DXFWINDOW_H
