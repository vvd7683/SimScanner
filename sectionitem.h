#ifndef SECTIONITEM_H
#define SECTIONITEM_H

#include <QTreeWidgetItem>

#include "qpefile.h"

class SectionItem : public QTreeWidgetItem
{
public:
    SectionItem(SSSection &sec_init, QTreeWidgetItem *parent = 0);
    SSSection &getSection() { return section; }
protected:
    SSSection &section;
};

#endif // SECTIONITEM_H
