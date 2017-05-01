#ifndef ENTROPYCHARTITEM_H
#define ENTROPYCHARTITEM_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtCharts/QChart>

#include "entropychartview.h"

class EntropyChartItem : public QTreeWidgetItem
{
public:
    explicit EntropyChartItem(QTreeWidgetItem *parent = 0);

    class TreeChart : public EntropyChartMini {
    public:
        TreeChart(QTreeWidget *ownerTree);
    public slots:
        void selectedItem();
    protected:
        const QtCharts::QChart::ChartTheme cDefault =
                QtCharts::QChart::ChartTheme::ChartThemeLight;
        const QtCharts::QChart::ChartTheme cHover =
                QtCharts::QChart::ChartTheme::ChartThemeBlueIcy;
        const QtCharts::QChart::ChartTheme cHighlighted =
                QtCharts::QChart::ChartTheme::ChartThemeBrownSand;
        QTreeWidget *tree;
    };
    TreeChart *chartView;
};

#endif // ENTROPYCHARTITEM_H
