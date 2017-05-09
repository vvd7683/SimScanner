#ifndef TRAININGSAMPLETYPEITEM_H
#define TRAININGSAMPLETYPEITEM_H

#include <QObject>
#include <QTreeWidgetItem>

#include "entropynn.h"
#include "entropy_parser.h"
#include "ss_types.h"
#include "ss_defs.h"

class TrainingSampleTypeItem : public QTreeWidgetItem
{
public:
    TrainingSampleTypeItem(const NNType c_type,
                           QTreeWidgetItem *parent = 0);
protected:
    const NNType c_nn_type;
    EntropyDiagram diagram;
};

#endif // TRAININGSAMPLETYPEITEM_H
