#include "entropyflowwindow.h"

EntropyFlowWindow::EntropyFlowWindow(unsigned char *Area,
                                     int AreaSz,
                                     int WindowSz,
                                     int StepSz,
                                     QObject *parent) : QObject(parent),
    step(StepSz),
    windowSz(WindowSz)
{
    for(int i = 0; i < AreaSz; ++i) {
        unsigned char *ptr = Area + i;
    }
}
