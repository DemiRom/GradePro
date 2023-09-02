
#ifndef GRADEPRO_LASERWINDOW_H
#define GRADEPRO_LASERWINDOW_H


#include "AbstractWindow.h"

class LaserWindow : public AbstractWindow {
public:
    explicit LaserWindow(std::string title) : AbstractWindow(std::move(title)) {}

    void Render() override;

    void HandleEvent(SDL_Event &event) override;
};


#endif //GRADEPRO_LASERWINDOW_H
