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

EntropyChartItem::TreeChart::TreeChart(QTreeWidget *ownerTree) : EntropyChartMini(),
    tree(ownerTree)
{
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
    chart()->setTheme(cDefault);
}
