#include "entropychartview.h"

EntropyChartView::EntropyChartView(QWidget *parent) : QtCharts::QChartView(parent)
{
    if(QtCharts::QChart *chart = new QtCharts::QChart) {
        if(QtCharts::QSplineSeries *series = new QtCharts::QSplineSeries) {
            series->append(0, 6);
            series->append(2, 4);
            series->append(3, 8);
            series->append(7, 4);
            series->append(10, 5);
            *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
            series->setName("spline");

            chart->legend()->hide();
            chart->addSeries(series);
            chart->setTitle("Simple spline chart example");
            chart->createDefaultAxes();
            chart->axisY()->setRange(0, 10);

            this->setChart(chart);
        }
    }
}
