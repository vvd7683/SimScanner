#ifndef TROJANDESCRIPTORITEM_H
#define TROJANDESCRIPTORITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QVector>
#include <QMap>

#include <opennn.h>
#include <tinyxml2.h>

#include "entropynn.h"
#include "nnitem.h"
#include "trainingsampleitem.h"
#include "trainingsampletypeitem.h"
#include "ss_defs.h"

class TrojanDescriptorItem : public QTreeWidgetItem
{
public:
    TrojanDescriptorItem(const QVector<SimScanNN *> &nns,
                         const SimScanNN::ssNNState c_state = SimScanNN::nnsDisabled,
                         QTreeWidgetItem *parent = 0);
    virtual ~TrojanDescriptorItem();
    bool train();
protected:
    QTreeWidgetItem *nn_profiles;
    QTreeWidgetItem *negative;
    QTreeWidgetItem *positive;
    QTreeWidgetItem *control;
    SimScanNN::ssNNState state;

    QVector<NNItem *> get_nn_to_train();
};

#endif // TROJANDESCRIPTORITEM_H
