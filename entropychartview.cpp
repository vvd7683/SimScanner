#include "entropychartview.h"

EntropyChartView::EntropyChartView(QWidget *parent) : QtCharts::QChartView(parent)
{
}

EntropyChartView::EntropyChartView(QVector<EntropyY> &points,
                                   QWidget *parent) : QtCharts::QChartView(parent)
{
    if(!add_points(points))
        throw;
}

void EntropyChartView::clear() {
    //
}

bool EntropyChartView::add_points(QVector<EntropyY> &points) {
    if(QtCharts::QChart *chart = new QtCharts::QChart) {
        if(QtCharts::QSplineSeries *series = new QtCharts::QSplineSeries) {
            EntropyY max_pt = 0., min_pt = 0.;
            foreach(const EntropyY pt, points) {
                max_pt = std::max(pt, max_pt);
                min_pt = std::min(pt, min_pt);
            }
            max_pt *= 1.1;
            if(min_pt < 0) min_pt *= 1.1; else min_pt = 0.;// /= 1.1;

            const int c_percent = (int)((points.size() / 100.) + .5);
            for(int i = 0; i < points.size(); i += c_percent) {
                const EntropyY c_pt = points[i];
                series->append(i, c_pt);
            }
            chart->legend()->hide();
            chart->addSeries(series);
            chart->setTitle("Entropy chart");
            chart->createDefaultAxes();
            chart->axisY()->setRange(min_pt, max_pt);

            chart->layout()->setContentsMargins(1, 1, 1, 1);
//            chart->setBackgroundRoundness(0);

            setChart(chart);

            return true;
        }
    }
    return false;
}
