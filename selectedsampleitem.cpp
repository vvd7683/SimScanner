#include "selectedsampleitem.h"

SelectedSampleItem::SelectedSampleItem(QFileInfo &file_info,
                                       QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    info(file_info)
{
    setText(0, info.fileName());
    setText(1,
                         QString(
                             ).sprintf(
                             "%d bytes",
                             info.size(
                                 )
                             )
                         );
    setText(2, info.absoluteFilePath());
}
