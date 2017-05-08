#include "qchartdialog.h"

QChartDialog::QChartDialog(SsMode mode, QWidget *parent) : QDialog(parent),
    chartEntropy(new EntropyChartView(this)),
    chartEntropyDerivative(new EntropyChartView(this)),
    chartMaximumDensity(new EntropyChartView(this)),
    chartMinimumDensity(new EntropyChartView(this)),
    chartExtremumDensity(new EntropyChartView(this)),

    ss_mode(mode)
{

}

QChartDialog::~QChartDialog() {
    delete chartEntropy;
    delete chartEntropyDerivative;
    delete chartExtremumDensity;
    delete chartMaximumDensity;
    delete chartMinimumDensity;
}

void QChartDialog::setCharts(EntropyDiagram &diagram) {
    QVector<EntropyY>pts;
    pts.resize(diagram.size());
    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].entropy_value;
    if(!chartEntropy->add_points(pts))
        throw;

    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].entropy_derivative_value;
    if(!chartEntropyDerivative->add_points(pts))
        throw;
    chartEntropyDerivative->chart()->setTitle(tr("Entropy derivative chart"));

    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].maximums_density;
    if(!chartMaximumDensity->add_points(pts))
        throw;
    chartMaximumDensity->chart()->setTitle(tr("Maximums density"));


    for(int i = 0; i < diagram.size(); ++i) pts[i] = diagram[i].minimums_density;
    if(!chartMinimumDensity->add_points(pts))
        throw;
    chartMinimumDensity->chart()->setTitle(tr("Minimums density"));

    for(int i = 0; i < diagram.size(); ++i) pts[i] += diagram[i].maximums_density;//Already contains minimums
    if(!chartExtremumDensity->add_points(pts))
        throw;
    chartExtremumDensity->chart()->setTitle(tr("Extremums density"));
}
