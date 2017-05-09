#ifndef TRAININGSAMPLEITEM_H
#define TRAININGSAMPLEITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QMap>

#include "entropynn.h"
#include "entropy_parser.h"
#include "ss_types.h"
#include "trainingsampletypeitem.h"

class TrainingSampleItem : public QTreeWidgetItem
{
public:
    explicit TrainingSampleItem(QTreeWidgetItem *parent = 0);
    void setDiagrams(QMap<NNType, EntropyDiagram> &diagrams);
};

#endif // TRAININGSAMPLEITEM_H
