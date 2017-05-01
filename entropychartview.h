#ifndef ENTROPYCHARTVIEW_H
#define ENTROPYCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>

#include "entropyflowwindow.h"

class EntropyChartView : public QtCharts::QChartView
{
    Q_OBJECT
public:
    explicit EntropyChartView(QWidget *parent = 0);
    explicit EntropyChartView(QVector<EntropyY> &points, QWidget *parent = 0);

    void clear();
    bool add_points(QVector<EntropyY> &points);

signals:

public slots:
};

typedef EntropyChartView ExtremumDensityChartView;

class EntropyChartMini : public EntropyChartView
{
    //
public:
    explicit EntropyChartMini(QWidget *parent = 0) : EntropyChartView(parent) {
        setFixedSize(200, 60);
        chart()->setMaximumHeight(60);
        chart()->setMaximumWidth(200);
        chart()->setMinimumHeight(60);
        chart()->setMinimumWidth(200);
        chart()->setTheme(QtCharts::QChart::ChartTheme::ChartThemeLight);
    }
};

#endif // ENTROPYCHARTVIEW_H
