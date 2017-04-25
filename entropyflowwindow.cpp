#include "entropyflowwindow.h"

EntropyFlowWindow::EntropyFlowWindow(PBYTE Area,
                                     int AreaSz,
                                     int WindowSz,
                                     int StepSz,
                                     QObject *parent) : QObject(parent),
    step(StepSz),
    windowSz(WindowSz)
{
    for(int i = 0; i < AreaSz; ++i) {
        PBYTE ptr = Area + i;
    }
}
