#include "entropychartitem.h"

EntropyChartItem::EntropyChartItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    chartView(Q_NULLPTR)
{
    if(QTreeWidget *tree = treeWidget()) {
        chartView = new TreeChart(tree);
        tree->setItemWidget(this, 1, chartView);
        QObject::connect(tree,
                         &QTreeWidget::itemSelectionChanged,
                         chartView,
                         &TreeChart::selectedItem);
    }
}

EntropyChartItem::TreeChart::TreeChart(QTreeWidget *ownerTree) : EntropyChartView(Q_NULLPTR),
    tree(ownerTree)
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
    foreach (QTreeWidgetItem *item, tree->selectedItems()) {
        if(EntropyChartItem *e_item = dynamic_cast<EntropyChartItem *>(item)) {
            if(e_item->chartView == this) {
                chart()->setTheme(cHighlighted);
                return;
            }
        }
    }
    chart()->setTheme(cDefault);//TODO: check for hover?
}

void EntropyChartItem::TreeChart::hoverItem(const int c_x, const int c_y) {
    if(QTreeWidgetItem *item = tree->itemAt(c_x, c_y)) {
        if(EntropyChartItem *e_item = dynamic_cast<EntropyChartItem *>(item)) {
            if(e_item->chartView == this) {
                if(chart()->theme() == cDefault)
                    chart()->setTheme(cHover);
                return;
            }
        }
    }
    if(chart()->theme() == cHover)
        chart()->setTheme(cDefault);
}
