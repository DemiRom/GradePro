#ifndef GRADEPRO_ABSTRACTWINDOW_H
#define GRADEPRO_ABSTRACTWINDOW_H

#include <string>
#include "SDL.h"

class AbstractWindow {
public:
    explicit AbstractWindow(std::string title) : title(std::move(title)) {};

    virtual void Render() = 0;
    virtual void HandleEvent(SDL_Event& event) = 0;

protected:
    std::string title;
    bool opened = true;


private:
};


#endif //GRADEPRO_ABSTRACTWINDOW_H
