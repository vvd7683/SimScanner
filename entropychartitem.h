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
    class TreeChart : public EntropyChartView {
    public:
        explicit TreeChart(QTreeWidget *ownerTree);
        static const QtCharts::QChart::ChartTheme cDefault =
                QtCharts::QChart::ChartTheme::ChartThemeLight;
        static const QtCharts::QChart::ChartTheme cHover =
                QtCharts::QChart::ChartTheme::ChartThemeBlueIcy;
        static const QtCharts::QChart::ChartTheme cHighlighted =
                QtCharts::QChart::ChartTheme::ChartThemeDark;

        void enterEvent(QEvent *event)  Q_DECL_OVERRIDE {
            if(chart()->theme() != cHighlighted)
                chart()->setTheme(cHover);
            event->accept();
        }

        void leaveEvent(QEvent *event)  Q_DECL_OVERRIDE {
            if(chart()->theme() != cHighlighted)
                chart()->setTheme(cDefault);
            event->accept();
        }
    public slots:
        void selectedItem();
        void hoverItem(const int c_x, const int c_y);//TODO: Use the same for EntropyChartView
    protected:
        QTreeWidget *tree;
    };
    TreeChart *chartView;
};

#endif // ENTROPYCHARTITEM_H
