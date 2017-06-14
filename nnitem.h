#ifndef NNITEM_H
#define NNITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class NNItem : public QTreeWidgetItem
{
public:
    explicit NNItem(QTreeWidgetItem *parent = 0);
protected:
    bool b_trained;
};

#endif // NNITEM_H
