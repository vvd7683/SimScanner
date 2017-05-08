#include "selectedsampleitem.h"

SelectedSampleItem::SelectedSampleItem(QFileInfo &file_info,
                                       QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    info(file_info)
{
}

QFileInfo &SelectedSampleItem::get_info() {
    return info;
}
