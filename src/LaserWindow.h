
#ifndef GRADEPRO_LASERWINDOW_H
#define GRADEPRO_LASERWINDOW_H


#include "AbstractWindow.h"

class LaserWindow : public AbstractWindow {
public:
    explicit LaserWindow(std::string title) : AbstractWindow(std::move(title)) {}

    void Render() override;

    void HandleEvent(SDL_Event &event) override;

private:
    double benchmark = 0.f; //Benchmark in M
    int benchmarkUnitIndex = 0; //M CM MM (0, 1, 2)
    int benchmarkReading = 0;
    double laserHeight = 0.f;

    int gradeReading = 0;
    double currentGradeElevation = 0.f;

    int expectedGradeReading = 0;
    double expectedElevation = 0.f;
    double expectedElevationOffset = 0.f;

    double gradeSlope = 0.f;
    int gradeDistance = 5;
    bool upDown = false;

    bool hiSet = false;
};


#endif //GRADEPRO_LASERWINDOW_H
