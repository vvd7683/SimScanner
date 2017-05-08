#ifndef QCHARTDIALOG_H
#define QCHARTDIALOG_H

#include <QDialog>

#include "entropychartview.h"
#include "ss_types.h"

class QChartDialog : public QDialog
{
public:
    explicit QChartDialog(SsMode mode = SsMode::ssmScan,
                          QWidget *parent = 0);
    ~QChartDialog();
protected:
    EntropyChartView *chartEntropy;
    EntropyChartView *chartEntropyDerivative;
    ExtremumDensityChartView *chartMaximumDensity;
    ExtremumDensityChartView *chartMinimumDensity;
    ExtremumDensityChartView *chartExtremumDensity;

    void setCharts(EntropyDiagram &diagram);

    SsMode ss_mode;

};

#endif // QCHARTDIALOG_H
