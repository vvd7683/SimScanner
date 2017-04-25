#ifndef ENTROPYCHARTVIEW_H
#define ENTROPYCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

#include "pe_parser/peParser.h"

class EntropyChartView : public QtCharts::QChartView
{
    Q_OBJECT
public:
    explicit EntropyChartView(QWidget *parent = 0);

    void clear();
    bool add_point(EntropyPoint pt);

signals:

public slots:
};

#endif // ENTROPYCHARTVIEW_H
