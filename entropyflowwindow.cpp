#include "entropyflowwindow.h"

EntropyFlowWindow::EntropyFlowWindow(unsigned char *Area,
                                     size_t AreaSz,
                                     size_t WindowSz,
                                     size_t StepSz,
                                     QObject *parent) : QObject(parent),
    step(StepSz),
    windowSz(WindowSz)
{
    const size_t cWinHalfSz = windowSz >> 1;
    Entropy entropy(Area, cWinHalfSz);
    for(size_t i = 0; i < AreaSz; ++i) {
        unsigned char &refChar = *(Area + i);
        if(i > cWinHalfSz)
            entropy.reduce_byte(refChar);
        if(i < AreaSz - cWinHalfSz)
            entropy.append_byte(refChar);
        const EntropyPoint pt = entropy.Value;
        points.push_back(pt);
    }
}
