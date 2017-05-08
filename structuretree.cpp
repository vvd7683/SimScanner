#include "structuretree.h"

StructureTree::StructureTree(QWidget *parent) : QTreeWidget(parent)
{
    QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
    __qtreewidgetitem->setText(2, QStringLiteral("3"));
    __qtreewidgetitem->setText(1, QStringLiteral("2"));
    __qtreewidgetitem->setText(0, QStringLiteral("1"));
    setHeaderItem(__qtreewidgetitem);
    //setObjectName(QStringLiteral("structureTree"));
    setColumnCount(3);
    setHeaderHidden(true);
    setColumnWidth(0, 300);
    setColumnWidth(1, 200);
    setColumnWidth(2, 200);

    setMouseTracking(true);
}

bool StructureTree::isTopItem(QTreeWidgetItem *item) {
    for(int i = 0; i < topLevelItemCount(); ++i) {
        if(item == topLevelItem(i))
            return true;
    }
    return false;
}

SectionItem *StructureTree::getSectionItem(QTreeWidgetItem *item) {
    if(!item)
        item = currentItem();
    while(item && (!isTopItem(item))) {
        if(SectionItem *sec_item = dynamic_cast<SectionItem *>(item)) {
            return sec_item;
        }
        item = item->parent();
    }
    return NULL;
}

SectionItem *StructureTree::getSectionItem(const QPoint &pos) {
    return getSectionItem(itemAt(pos));
}
