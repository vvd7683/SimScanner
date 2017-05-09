#include "nnitem.h"

NNItem::NNItem(SimScanNN &init_nn,
               QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    nn(init_nn)
{
    if(EntropyFixedNN *ef_nn = dynamic_cast<EntropyFixedNN *>(&nn)) {
        //setText();
        return;
    }
    if(EntropyRelativeNN *er_nn = dynamic_cast<EntropyRelativeNN *>(&nn)) {
        return;
    }
}
