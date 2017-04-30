#include "entropychartview.h"

EntropyChartView::EntropyChartView(QWidget *parent) : QtCharts::QChartView(parent)
{
    /*
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
    */
}

EntropyChartView::EntropyChartView(QVector<EntropyY> &points, QWidget *parent) : QtCharts::QChartView(parent) {
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

            setChart(chart);

            return true;
        }
    }
    return false;
}
