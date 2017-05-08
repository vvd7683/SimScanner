#include "selectedsampleitem.h"

SelectedSampleItem::SelectedSampleItem(const QModelIndex c_idx,
                                       QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    c_index(c_idx)
{
}

const QModelIndex SelectedSampleItem::get_index() {
    return c_index;
}
