#include "entropyflowwindow.h"
#include <QMessageBox>

EntropyFlowWindow::EntropyFlowWindow(unsigned char *Area,
                                     size_t AreaSz,
                                     size_t WindowSz,
                                     size_t StepSz,
                                     QObject *parent) : QObject(parent),
    step(StepSz),
    windowSz(WindowSz)
{
    const size_t cWinHalfSz = windowSz >> 1;
    if(cWinHalfSz < AreaSz) {
        Entropy entropy(Area, cWinHalfSz);
        for(size_t i = 1; i < AreaSz; ++i) {
            const EntropyPoint pt = entropy.Value;
            points.push_back(pt);
            if(i < AreaSz - cWinHalfSz)
                entropy.append_byte(*(Area + PRED(cWinHalfSz) + i));
            if(i > cWinHalfSz)
                entropy.reduce_byte(*(Area - SUCC(cWinHalfSz) + i));
            derivative_points.push_back(entropy.Value - pt);
        }
    } else {
        //plateau - area is less than frame
        Entropy entropy(Area, AreaSz);
        for(size_t i = 0; i < AreaSz; ++i) {
            points.push_back(entropy.Value);
            derivative_points.push_back(0.);
        }
    }
}

EntropyDiagram EntropyFlowWindow::get_points() { return points; }

EntropyDiagram EntropyFlowWindow::get_derivative() { return derivative_points; }
