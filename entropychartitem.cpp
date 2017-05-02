#include "entropychartitem.h"

EntropyChartItem::EntropyChartItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    chartView(Q_NULLPTR)
{
    if(QTreeWidget *tree = treeWidget()) {
        chartView = new TreeChart(this);
        tree->setItemWidget(this, 1, chartView);
        QObject::connect(tree,
                         &QTreeWidget::itemSelectionChanged,
                         chartView,
                         &TreeChart::selectedItem);
    }
}

EntropyChartItem::TreeChart::TreeChart(QTreeWidgetItem *ownerItem,
                                       QWidget *parent) : EntropyChartView(parent),
    owner_item(ownerItem)
{
    setFixedSize(200, 60);
    chart()->setMaximumHeight(60);
    chart()->setMaximumWidth(200);
    chart()->setMinimumHeight(60);
    chart()->setMinimumWidth(200);
    chart()->setTheme(QtCharts::QChart::ChartTheme::ChartThemeLight);

    setMouseTracking(true);

    chart()->setTheme(cDefault);
}

void EntropyChartItem::TreeChart::selectedItem() {
    chart()->setTheme(owner_item->isSelected() ? cHighlighted : cDefault);
}

void EntropyChartItem::TreeChart::hoverItem(QTreeWidgetItem *item) {
    if(owner_item->isSelected())
        return;
    if(item == owner_item) {
        if(chart()->theme() == cDefault)
            chart()->setTheme(cHover);
    } else {
        if(chart()->theme() == cHover)
            chart()->setTheme(cDefault);
    }
}
