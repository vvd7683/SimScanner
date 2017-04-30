#include "entropyflowwindow.h"
#include <QMessageBox>

EntropyFlowWindow::EntropyFlowWindow(unsigned char *Area,
                                     size_t AreaSz,
                                     size_t WindowSz,
                                     QObject *parent) : QObject(parent),
    cWindowSz(WindowSz)
{
    const size_t cWinHalfSz = cWindowSz >> 1;
    points.resize(AreaSz);
    if(cWinHalfSz < AreaSz) {
        ExtremumPoints maximums, minimums;
        Entropy entropy(Area, cWinHalfSz);
        points[0].entropy_value = entropy.Value;
        points[0].entropy_derivative_value = 0.;
        points[0].extremums_density = 0.;
        for(size_t i = 1; i < AreaSz; ++i) {
            const EntropyX c_abs = (EntropyX)i;
            EntropyPoint &pt = points[i];
            pt.entropy_value = entropy.Value;
            if(c_abs < (EntropyX)AreaSz - (EntropyX)cWinHalfSz)
                entropy.append_byte(*(Area + PRED(cWinHalfSz) + i));
            if(c_abs > cWinHalfSz)
                entropy.reduce_byte(*(Area - SUCC(cWinHalfSz) + i));
            const EntropyY c_cur_delta = entropy.Value - pt.entropy_value;
            pt.entropy_derivative_value = c_cur_delta;
            const EntropyY c_prev_delta = points[PRED(i)].entropy_derivative_value;
            switch(const EntropyDirection edir = e_dir(c_prev_delta, c_cur_delta))
            {
            case edirMax:
            {
                maximums.push_back(ExtremumPoint(c_abs, edir));
                break;
            }
            case edirMin:
            {
                minimums.push_back(ExtremumPoint(c_abs, edir));
                break;
            }
            case edirNo:
            default:
                break;
            }
            if(c_abs > cWinHalfSz) {
                const EntropyX c_extremum_calc_x = c_abs - cWinHalfSz;
                const EntropyX cFrameSz =
                        c_extremum_calc_x > cWinHalfSz ?
                            (EntropyX)cWindowSz :
                            cWinHalfSz + c_extremum_calc_x;
                const EntropyX c_lower = c_extremum_calc_x - (EntropyX)cWindowSz;

                while(minimums[0].X < c_lower)
                    minimums.remove(0);
                while(maximums[0].X < c_lower)
                    maximums.remove(0);
                const EntropyY c_density = maximums.size() / cFrameSz;
                points[c_extremum_calc_x].extremums_density = c_density;
            }
        }
        for(size_t i = AreaSz - cWinHalfSz; i < AreaSz; ++i) {
            const EntropyX c_extremum_calc_x = (EntropyX)i;
            const EntropyX cFrameSz = AreaSz - i + cWinHalfSz;
            const EntropyX c_lower = c_extremum_calc_x - (EntropyX)cWindowSz;

            while(minimums[0].X < c_lower)
                minimums.remove(0);
            while(maximums[0].X < c_lower)
                maximums.remove(0);
            const EntropyY c_density = maximums.size() / cFrameSz;
            EntropyPoint &pt = points[c_extremum_calc_x];
            pt.extremums_density = c_density;
        }
    } else {
        //plateau - area is less than frame
        Entropy entropy(Area, AreaSz);
        for(size_t i = 0; i < AreaSz; ++i) {
            points.push_back({entropy.Value, 0., 0.});
        }
    }
}

EntropyDiagram EntropyFlowWindow::get_points() { return points; }
