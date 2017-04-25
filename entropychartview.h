#ifndef ENTROPYCHARTVIEW_H
#define ENTROPYCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

class EntropyChartView : public QtCharts::QChartView
{
    Q_OBJECT
public:
    explicit EntropyChartView(QWidget *parent = 0);

signals:

public slots:
};

#endif // ENTROPYCHARTVIEW_H
