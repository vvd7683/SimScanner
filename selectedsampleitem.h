#ifndef SELECTEDSAMPLEITEM_H
#define SELECTEDSAMPLEITEM_H

#include <QTreeWidgetItem>
#include <QFileInfo>

class SelectedSampleItem : public QTreeWidgetItem
{
public:
    SelectedSampleItem(QFileInfo &file_info, QTreeWidgetItem *parent = 0);
protected:
    QFileInfo info;
};

#endif // SELECTEDSAMPLEITEM_H
