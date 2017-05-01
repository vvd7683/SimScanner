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
