#ifndef SELECTEDSAMPLEITEM_H
#define SELECTEDSAMPLEITEM_H

#include <QTreeWidgetItem>
#include <QFileInfo>

class SelectedSampleItem : public QTreeWidgetItem
{
public:
    SelectedSampleItem(const QModelIndex c_idx, QTreeWidgetItem *parent = 0);
    const QModelIndex get_index();
protected:
    const QModelIndex c_index;
};

#endif // SELECTEDSAMPLEITEM_H
