#include "trainingsampleitem.h"

TrainingSampleItem::TrainingSampleItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{

}

void TrainingSampleItem::setDiagrams(QMap<NNType, EntropyDiagram> &diagrams) {
    foreach(NNType nn_type, diagrams.keys()) {
        const EntropyDiagram &diagram = diagrams.value(nn_type);
        TrainingSampleTypeItem *child = new TrainingSampleTypeItem(nn_type, this);
        //TODO: set diagram to child
    }
}
