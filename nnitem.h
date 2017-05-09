#ifndef NNITEM_H
#define NNITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include <opennn.h>
#include <tinyxml2.h>

#include "entropynn.h"

class NNItem : public QTreeWidgetItem
{
public:
    explicit NNItem(SimScanNN &init_nn,
                    QTreeWidgetItem *parent = 0);
    SimScanNN::ssNNState getState() { return nn.getState(); }
    SimScanNN::ssNNType getType() { return nn.getNnType(); }
protected:
    SimScanNN &nn;
    bool b_trained;
};

#endif // NNITEM_H
