#include "trainingsampletypeitem.h"

TrainingSampleTypeItem::TrainingSampleTypeItem(const NNType c_type,
                                               QTreeWidgetItem *parent) : QTreeWidgetItem(parent), c_nn_type(c_type)
{
    setText(0, getNnTypes().value(c_nn_type));
}
