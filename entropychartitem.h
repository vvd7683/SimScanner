#ifndef ENTROPYCHARTITEM_H
#define ENTROPYCHARTITEM_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtCharts/QChart>
#include <QVector>
#include <QGraphicsLayout>

#include "entropychartview.h"

class EntropyChartItem : public QTreeWidgetItem
{
public:
    explicit EntropyChartItem(QVector<EntropyY> &pts, QTreeWidgetItem *parent = 0);
    class TreeChart : public EntropyChartView {
    public:
        explicit TreeChart(QTreeWidgetItem *ownerItem,
                           QVector<EntropyY> &pts,
                           QWidget *parent = 0);
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
        void hoverItem(QTreeWidgetItem *item);//TODO: Use the same for EntropyChartView
    protected:
        QTreeWidgetItem *owner_item;
    };
    TreeChart *chartView;
};

#endif // ENTROPYCHARTITEM_H
